int main() {
setuid(1001);
execlp("/bin/sh", "/bin/sh", 0);
return 0;
}
