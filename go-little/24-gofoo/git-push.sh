#!/bin/sh
set -e -x
cd 24-gofoo
rm -rf .git
git init
git add foo.go
git commit -m "Add foo.go"
git remote add origin https://bitbucket.org/susam/gofoo.git
git push -u -f origin master
rm -rf .git
