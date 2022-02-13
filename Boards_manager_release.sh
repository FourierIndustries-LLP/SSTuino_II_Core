#!/bin/bash
set -euo pipefail # stop script upon error of any command

##########################################################
##                                                      ##
## Shell script for generating a boards manager release ##
## Created by MCUdude                                   ##
## Modified by d3lta-v for the SSTuino II               ##
## Requires wget, jq and a bash environment             ##
##                                                      ##
##########################################################

#### Instructions for usage
# 1. Create a new release on GitHub. The tag name must be in the format "v1.0.0" as this script relies on it
# 2. Ensure that the same folder has an existing .json file (which is in the format of package_${AUTHOR}_${REPOSITORY}_index.json)
# 3. This script will automatically package up the latest release as a bz2 file, and update the index.json file to contain the latest release
# 4. Once the updates are pushed to the gh-pages branch of the repo, the Github Pages will be updated accordingly
#
# If you are rebuilding for an existing build number, please delete the old JSON entry manually before

# Change these to match your repo
AUTHOR=FourierIndustries-LLP       # Github username
REPOSITORY=SSTuino_II_Core         # Github repo name
PLATFORM_NAME="SSTuino II Series Boards"

# Get the download URL for the latest release from Github
DOWNLOAD_URL=$(curl -s https://api.github.com/repos/$AUTHOR/$REPOSITORY/releases/latest | grep "tarball_url" | awk -F\" '{print $4}')

# Download file
wget --no-verbose $DOWNLOAD_URL

# Get filename (the filename will always be the version number in the format v1.0.0 without extensions)
DOWNLOADED_FILE=$(echo $DOWNLOAD_URL | awk -F/ '{print $8}')

# Add .tar.bz2 extension to downloaded file
mv $DOWNLOADED_FILE ${DOWNLOADED_FILE}.tar.bz2

# Extract downloaded file and place it in a folder
printf "\nExtracting folder ${DOWNLOADED_FILE}.tar.bz2 to $REPOSITORY-${DOWNLOADED_FILE#"v"}\n"
mkdir -p "$REPOSITORY-${DOWNLOADED_FILE#"v"}" && tar -xzf ${DOWNLOADED_FILE}.tar.bz2 -C "$REPOSITORY-${DOWNLOADED_FILE#"v"}" --strip-components=1
printf "Done!\n"

# Move files out of the megaavr folder
printf "\nModifiying folder structure\n"
mv $REPOSITORY-${DOWNLOADED_FILE#"v"}/megaavr/* $REPOSITORY-${DOWNLOADED_FILE#"v"}
printf "Done!\n"

# Delete downloaded file and empty megaavr folder
rm -rf ${DOWNLOADED_FILE}.tar.bz2 $REPOSITORY-${DOWNLOADED_FILE#"v"}/megaavr

# Compress folder to tar.bz2
printf "\nCompressing folder $REPOSITORY-${DOWNLOADED_FILE#"v"} to $REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2\n"
tar -cjSf $REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2 $REPOSITORY-${DOWNLOADED_FILE#"v"}
printf "Done!\n"

# Get file size on bytes
printf "\nComputing file size and hash\n"
FILE_SIZE=$(wc -c "$REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2" | awk '{print $1}')
# Get SHA256 hash
SHA256="SHA-256:$(shasum -a 256 "$REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2" | awk '{print $1}')"
printf "Done!\n"

# Create Github download URL
URL="https://${AUTHOR}.github.io/${REPOSITORY}/$REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2"

cp "package_${AUTHOR}_${REPOSITORY}_index.json" "package_${AUTHOR}_${REPOSITORY}_index.json.tmp"

# Add new boards release entry into the existing JSON
# NOTE: Please ensure that the "boards" parameter is correct before running this script
jq -r                                      \
--arg repository    $REPOSITORY            \
--arg platform_name $PLATFORM_NAME         \
--arg version       ${DOWNLOADED_FILE#"v"} \
--arg url           $URL                   \
--arg checksum      $SHA256                \
--arg file_size     $FILE_SIZE             \
--arg file_name     $REPOSITORY-${DOWNLOADED_FILE#"v"}.tar.bz2  \
'.packages[].platforms[.packages[].platforms | length] |= . +
{
  "name": $platform_name,
  "architecture": "megaavr",
  "version": $version,
  "category": "Contributed",
  "url": $url,
  "archiveFileName": $file_name,
  "checksum": $checksum,
  "size": $file_size,
  "boards": [
    {"name": "SSTuino II"}
  ],
  "toolsDependencies": [
    {
      "packager": "arduino",
      "name": "avr-gcc",
      "version": "7.3.0-atmel3.6.1-arduino7"
    },
    {
      "packager": "arduino",
      "name": "avrdude",
      "version": "6.3.0-arduino18"
    },
    {
      "packager": "arduino",
      "name": "arduinoOTA",
      "version": "1.3.0"
    }
  ]
}' "package_${AUTHOR}_${REPOSITORY}_index.json.tmp" > "package_${AUTHOR}_${REPOSITORY}_index.json"

# Remove files that's no longer needed
rm -rf "$REPOSITORY-${DOWNLOADED_FILE#"v"}" "package_${AUTHOR}_${REPOSITORY}_index.json.tmp"
