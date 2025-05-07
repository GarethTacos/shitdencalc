// main updater mechanism
// fetch.c is to fetch the new JSON with curl
// and jsonparse is to parse the JSON
// and compare versions between versionc.json (current version)
// and versionn.json (new version)
// if new version's number is greater than current version
// prompt for upgrade
// if new version's number is less than current version
// warn the user that there might be errors in this build
// or the repo itself
// if same version, do not upgrade
