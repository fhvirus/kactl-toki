alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 \
	-fsanitize=undefined,address -DNONTOI'
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'
