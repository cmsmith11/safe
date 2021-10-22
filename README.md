# File Encrypt / Decrypt Script

## safe.cpp:
Takes single file as argument, prompts user for key seed (or takes as argument), then produces encrypted file using one-time-pad symmetric encryption using a pseudo-random key generated by LFSR using the user provided key seed as a starting point. Build using "g++ safe.cpp -o safe". Run without any arguments for help. To recover file from encrypted, simply encrypt the encrypted file with the same key seed.

## enc.sh:
Takes source and destination directories and secret as arguments (run without any arguments for more details). Encrypts all files in the source directory and puts them into the destination directory. Encryption on each file uses the user provided secret, with a NONCE appended to it, for additional security, to ensure no two files are encrypted using the same key. Encryption is symmetric, so to unencrypt a directory, you would just apply the same secret passcode to the encrypted directory to recover the original files.

## Test:
To test, simply run "./enc.sh test encrypted secret", which will generate a new directory called "encryted" containing all files in "test" encrypted with the secret key seed starter "secret". You may inspect the files to see that they are unintelligible. Then, run "./enc.sh encrypted decrypted secret", which will create a new directory "decrypted" containing files which match up perfectly to their original versions from "test". Caution: once you encrypt a directory, do NOT delete, edit, or change the names to any files, as decrypting depends on the order and content of every single file in order to decrypt properly.
