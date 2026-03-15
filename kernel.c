void kernel_main() {
    char* video = (char*)0xB8000;
    char* msg = "N0t-OS v2.0 - DISTRIBUTION READY!";
    
    while(*msg) {
        *video++ = *msg++;
        *video++ = 0x07;
    }
    
    while(1);
}