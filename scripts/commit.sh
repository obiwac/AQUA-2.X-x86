
#!/bin/bash

echo -n "Enter your commit message "
read message;

git add . --verbose;
git commit -m "$message" --verbose;
git push origin master --verbose;

make pci-database;

exit;
