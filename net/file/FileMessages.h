enum {
    /* Client -> Server */
    kCli2File_PingRequest = 0,
    kCli2File_BuildIdRequest = 10,
    kCli2File_ManifestRequest = 20,
    kCli2File_FileDownloadRequest = 21,
    kCli2File_ManifestEntryAck = 22,
    kCli2File_FileDownloadChunkAck = 23,
};

enum {
    /* Server -> Client */
    kFile2Cli_PingReply = 0,
    kFile2Cli_BuildIdReply = 10,
    kFile2Cli_BuildIdUpdate = 11,
    kFile2Cli_ManifestReply = 20,
    kFile2Cli_FileDownloadReply = 21,
};
