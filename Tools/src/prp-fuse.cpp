#define FUSE_USE_VERSION 25
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <Debug/plDebug.h>
#include <ResManager/plResManager.h>
#include <ResManager/plFactory.h>
#include <Stream/hsRAMStream.h>
#include <PRP/KeyedObject/hsKeyedObject.h>

#define PAGEINFO "PageInfo.prc"

static time_t s_fatime = 0, s_fmtime = 0, s_fctime = 0;
static uid_t s_uid = 0;
static gid_t s_gid = 0;

struct _clsType {
    const char* clsName;
    short clsIdx;
};
typedef std::vector<_clsType> CLASSLIST;

static struct _session {
    plResManager resMan;
    plPageInfo* page;
    CLASSLIST classes;
} *s_session = NULL;

#define RESMGR  (s_session->resMan)
#define PAGE    (s_session->page)
#define CLASSES (s_session->classes)

void CacheFile(struct FileCache* obj);
void DecacheFile(size_t fh);

struct FileCache {
    long refs;
    unsigned char* prcdata;
    size_t prcsize;
    unsigned char* objdata;
    size_t objsize;

    // Object identification
    plKey key;
    size_t fh;

    FileCache() : refs(1)
    {
        CacheFile(this);
    }

    ~FileCache()
    {
        delete[] prcdata;
        delete[] objdata;
        DecacheFile(fh);
    }

    void ref()
    {
        ++refs;
    }

    void unref()
    {
        if (--refs == 0)
            delete this;
    }
};

typedef std::vector<FileCache*> FILELIST;
static FILELIST s_openfiles;

static char* s_pageInfoPrc = NULL;
static size_t s_pageInfoPrcSize = 0;

void CacheFile(struct FileCache* obj)
{
    for (size_t i=0; i<s_openfiles.size(); i++) {
        if (s_openfiles[i] == NULL) {
            obj->fh = i + 1;
            s_openfiles[i] = obj;
            return;
        }
    }

    // No empty space, allocate some new room and store it there
    obj->fh = s_openfiles.size() + 1;
    s_openfiles.resize(s_openfiles.size() + 8);
    s_openfiles[obj->fh - 1] = obj;
}

void DecacheFile(size_t fh)
{
    s_openfiles[fh-1] = NULL;
}

static int prp_getattr(const char* path, struct stat* stbuf)
{
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0555;
        stbuf->st_nlink = 2 + CLASSES.size();
        stbuf->st_uid = s_uid;
        stbuf->st_gid = s_gid;
        stbuf->st_atime = s_fatime;
        stbuf->st_mtime = s_fmtime;
        stbuf->st_ctime = s_fctime;
    } else if (strcmp(path, "/" PAGEINFO) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_uid = s_uid;
        stbuf->st_gid = s_gid;
        stbuf->st_size = 0;
        stbuf->st_atime = s_fatime;
        stbuf->st_mtime = s_fmtime;
        stbuf->st_ctime = s_fctime;
    } else {
        // Find the type first
        plString typeStr = plString(path + 1).beforeFirst('/');
        if (typeStr.empty())
            return -ENOENT;
        short type = plFactory::ClassIndex(typeStr);
        if (type < 0)
            return -ENOENT;

        // Make sure the type is actually present
        bool hasType = false;
        for (CLASSLIST::iterator it = CLASSES.begin(); it != CLASSES.end() && !hasType; it++) {
            if (it->clsIdx == type)
                hasType = true;
        }
        if (!hasType)
            return -ENOENT;

        plString fname = plString(path + 1).afterFirst('/');
        if (fname.empty()) {
            // Directory
            stbuf->st_mode = S_IFDIR | 0555;
            stbuf->st_nlink = 2 + RESMGR.getKeys(PAGE->getLocation(), type).size();
            stbuf->st_uid = s_uid;
            stbuf->st_gid = s_gid;
            stbuf->st_atime = s_fatime;
            stbuf->st_mtime = s_fmtime;
            stbuf->st_ctime = s_fctime;
        } else {
            // File
            plString ftype = fname.afterLast('.');
            fname = fname.beforeLast('.');
            std::vector<plKey> keys = RESMGR.getKeys(PAGE->getLocation(), type);
            for (std::vector<plKey>::iterator it = keys.begin(); it != keys.end(); it++) {
                if (CleanFileName((*it)->getName()) == fname) {
                    stbuf->st_mode = S_IFREG | 0444;
                    stbuf->st_nlink = 1;
                    stbuf->st_uid = s_uid;
                    stbuf->st_gid = s_gid;
                    stbuf->st_size = (ftype == "po") ? (*it)->getObjSize() : 0;
                    stbuf->st_atime = s_fatime;
                    stbuf->st_mtime = s_fmtime;
                    stbuf->st_ctime = s_fctime;
                    return 0;
                }
            }
            return -ENOENT;
        }
    }
    return 0;
}

static int prp_open(const char* path, fuse_file_info* fi)
{
    // Check if this is the special PageInfo file
    if (strcmp(path, "/" PAGEINFO) == 0) {
        fi->fh = 0;
        return 0;
    }

    // Get the type
    plString typeStr = plString(path + 1).beforeFirst('/');
    if (typeStr.empty())
        return -ENOENT;
    short type = plFactory::ClassIndex(typeStr);
    if (type < 0)
        return -ENOENT;

    // Make sure the object is actually present (O_CREAT is already handled)
    plString oname = plString(path + 1).afterFirst('/').beforeLast('.');
    plKey myKey;
    std::vector<plKey> keys = RESMGR.getKeys(PAGE->getLocation(), type);
    for (std::vector<plKey>::iterator it = keys.begin(); it != keys.end(); it++) {
        if ((*it)->getName() == oname)
            myKey = *it;
    }
    if (!myKey.Exists())
        return -ENOENT;

    // Look for an already-open object:
    for (FILELIST::iterator it = s_openfiles.begin(); it != s_openfiles.end(); it++) {
        if ((*it)->key == myKey) {
            if ((fi->flags & (O_RDWR | O_WRONLY)) != 0)
                return -EACCES;
            (*it)->ref();
            fi->fh = (*it)->fh;
            return 0;
        }
    }

    // First time to open:
    FileCache* fc = new FileCache();
    fc->key = myKey;

    // Cache the object raw data
    {
        hsRAMStream RS(RESMGR.getVer());
        myKey->getObj()->write(&RS, &RESMGR);
        fc->objsize = RS.size();
        fc->objdata = new unsigned char[fc->objsize];
        RS.copyTo(fc->objdata, fc->objsize);
    }

    // Cache the PRC data
    {
        hsRAMStream RS(RESMGR.getVer());
        pfPrcHelper prc(&RS);
        myKey->getObj()->prcWrite(&prc);
        fc->prcsize = RS.size();
        fc->prcdata = new unsigned char[fc->prcsize];
        RS.copyTo(fc->prcdata, fc->prcsize);
    }
    return 0;
}

static int prp_read(const char* path, char* buf, size_t size, off_t offset,
                    fuse_file_info* fi)
{
    if (strcmp(path, "/" PAGEINFO) == 0) {
        // TODO
        return -1;
    }

    plString ext = plString(path).afterLast('.');
    FileCache* fc = s_openfiles[fi->fh - 1];
    if (ext == "prc") {
        if (offset >= fc->prcsize)
            return 0;
        if (offset + size > fc->prcsize)
            size = fc->prcsize - offset;
        memcpy(buf, fc->prcdata + offset, size);
        return size;
    } else if (ext == "po") {
        if (offset >= fc->objsize)
            return 0;
        if (offset + size > fc->objsize)
            size = fc->objsize - offset;
        memcpy(buf, fc->objdata + offset, size);
        return size;
    } else {
        return -ENOENT;
    }
}

static int prp_readdir(const char* path, void* buf, fuse_fill_dir_t filler,
                       off_t offset, fuse_file_info* fi)
{
    if (strcmp(path, "/") == 0) {
        // PRP Root:
        filler(buf, ".", NULL, 0);
        filler(buf, "..", NULL, 0);
        filler(buf, PAGEINFO, NULL, 0);

        // PRP Types:
        for (CLASSLIST::iterator it = CLASSES.begin(); it != CLASSES.end(); it++)
            filler(buf, it->clsName, NULL, 0);
        return 0;
    } else {
        // Type directory
        plString typeStr = plString(path + 1);
        if (typeStr.empty())
            return -ENOENT;
        short type = plFactory::ClassIndex(typeStr);
        if (type < 0)
            return -ENOENT;

        // Make sure the type is actually present
        bool hasType = false;
        for (CLASSLIST::iterator it = CLASSES.begin(); it != CLASSES.end() && !hasType; it++) {
            if (it->clsIdx == type)
                hasType = true;
        }
        if (!hasType)
            return -ENOENT;

        filler(buf, ".", NULL, 0);
        filler(buf, "..", NULL, 0);
        std::vector<plKey> keys = RESMGR.getKeys(PAGE->getLocation(), type);
        for (std::vector<plKey>::iterator it = keys.begin(); it != keys.end(); it++) {
            filler(buf, CleanFileName((*it)->getName() + ".po"), NULL, 0);
            filler(buf, CleanFileName((*it)->getName() + ".prc"), NULL, 0);
        }
        return 0;
    }
}

static fuse_operations prp_oper = {
    /* COMPAT: V25 */
    &prp_getattr,           /* getattr */
    NULL,                   /* readlink */
    NULL,                   /* getdir */
    NULL,                   /* mknod */
    NULL,                   /* mkdir */
    NULL,                   /* unlink */
    NULL,                   /* rmdir */
    NULL,                   /* symlink */
    NULL,                   /* rename */
    NULL,                   /* link */
    NULL,                   /* chmod */
    NULL,                   /* chown */
    NULL,                   /* truncate */
    NULL,                   /* utime */
    &prp_open,              /* open */
    &prp_read,              /* read */
    NULL,                   /* write */
    NULL,                   /* statfs */
    NULL,                   /* flush */
    NULL,                   /* release */
    NULL,                   /* fsync */
    NULL,                   /* setxattr */
    NULL,                   /* getxattr */
    NULL,                   /* listxattr */
    NULL,                   /* removexattr */
    NULL,                   /* opendir */
    &prp_readdir,           /* readdir */
    NULL,                   /* releasedir */
    NULL,                   /* fsyncdir */
    NULL,                   /* init */
    NULL,                   /* destroy */
    NULL,                   /* access */
    NULL,                   /* create */
    NULL,                   /* ftruncate */
    NULL,                   /* fgetattr */
};

static void printUsage(char* progName)
{
    fprintf(stderr, "Usage: %s <prp-file> [fuse options] <mount-point>\n", progName);
}

int main(int argc, char* argv[])
{
    plDebug::InitFile(plDebug::kDLAll, "prp-fuse.log");

    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    s_session = new _session;
    PAGE = RESMGR.ReadPage(argv[1]);
    if (PAGE == NULL)
        return 1;

    std::vector<short> types = RESMGR.getTypes(PAGE->getLocation());
    CLASSES.resize(types.size());
    for (size_t i=0; i<types.size(); i++) {
        CLASSES[i].clsName = plFactory::ClassName(types[i]);
        CLASSES[i].clsIdx = types[i];
    }

    struct stat stbuf;
    stat(argv[1], &stbuf);
    s_uid = stbuf.st_uid;
    s_gid = stbuf.st_gid;
    s_fatime = stbuf.st_atime;
    s_fmtime = stbuf.st_mtime;
    s_fctime = stbuf.st_ctime;

    return fuse_main(argc - 1, argv + 1, &prp_oper);
}
