char next_key(char key) {
    unsigned char k = 1;
    key = (key >> k) | (key << (sizeof(key) * 8 - k));
    return key;
}




