/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

enum /* Client -> Server */
{
    kCli2File_PingRequest = 0,
    kCli2File_BuildIdRequest = 10,
    kCli2File_ManifestRequest = 20,
    kCli2File_FileDownloadRequest = 21,
    kCli2File_ManifestEntryAck = 22,
    kCli2File_FileDownloadChunkAck = 23,
};

enum /* Server -> Client */
{
    kFile2Cli_PingReply = 0,
    kFile2Cli_BuildIdReply = 10,
    kFile2Cli_BuildIdUpdate = 11,
    kFile2Cli_ManifestReply = 20,
    kFile2Cli_FileDownloadReply = 21,
};
