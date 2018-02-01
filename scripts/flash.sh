
#!/bin/bash

echo -n "Press enter to continue ... ";
read none;

dir /dev/sd*;
echo -n "Enter drive name ";

read drive;
sudo dd if=aqua/aqua.iso of=/dev/$drive;

exit;
