@echo off
git status
git add .
git status
git commit -m "auto"
git pull origin master
git push origin master
