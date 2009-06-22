#define FUSE_USE_VERSION 25
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <ResManager/plResManager.h>
#include <ResManager/plFactory.h>
#include <Stream/hsRAMStream.h>

#define PAGEINFO "pageinfo.prc"

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
    /* COMPAT: V2 */
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
    NULL,                   /* open */
    NULL,                   /* read */
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
    s_uid = getuid();
    s_gid = getgid();

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

    return fuse_main(argc - 1, argv + 1, &prp_oper);
}
