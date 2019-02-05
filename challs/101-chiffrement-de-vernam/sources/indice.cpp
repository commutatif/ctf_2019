// Vernam's cipher requires a random which is as long as the messages.
// Furthermore, one should not re-use the same random band a second time.
// Else, very bad things might happen...

// this is the frequencies of each characters in the 8 plaintexts
double score(unsigned char c) {
    switch (c) {
	case 10: return 0.0174479;   //\n
	case 32: return 0.145468;    //space
	case 34: return 0.0024778;   //"
	case 39: return 0.00185835;  //'
	case 40: return 0.00206484;  //(
	case 41: return 0.00206484;  //)
	case 43: return 0.000103242; //+
	case 44: return 0.0111501;   //,
	case 45: return 0.00175511;  //-
	case 46: return 0.00794962;  //.
	case 48: return 0.00196159;  //0
	case 49: return 0.00134214;  //1
	case 50: return 0.00165187;  //2
	case 51: return 0.000309725; //3
	case 52: return 0.000516209; //4
	case 53: return 0.000206484; //5
	case 54: return 0.000309725; //6
	case 55: return 0.000309725; //7
	case 56: return 0.000412967; //8
	case 57: return 0.000825934; //9
	case 58: return 0.000722693; //:
	case 59: return 0.000206484; //;
	case 65: return 0.00185835;  //A
	case 66: return 0.000412967; //B
	case 67: return 0.00299401;  //C
	case 68: return 0.000929176; //D
	case 69: return 0.00165187;  //E
	case 70: return 0.00196159;  //F
	case 71: return 0.000103242; //G
	case 72: return 0.000619451; //H
	case 73: return 0.00206484;  //I
	case 74: return 0.000103242; //J
	case 75: return 0.000103242; //K
	case 76: return 0.00154863;  //L
	case 77: return 0.00165187;  //M
	case 78: return 0.000309725; //N
	case 79: return 0.000619451; //O
	case 80: return 0.000929176; //P
	case 82: return 0.000929176; //R
	case 83: return 0.00206484;  //S
	case 84: return 0.00268429;  //T
	case 85: return 0.000412967; //U
	case 86: return 0.000412967; //V
	case 87: return 0.00154863;  //W
	case 89: return 0.000516209; //Y
	case 97: return 0.068759;    //a
	case 98: return 0.0111501;   //b
	case 99: return 0.0294239;   //c
	case 100: return 0.0265331;  //d
	case 101: return 0.09395;    //e
	case 102: return 0.0132149;  //f
	case 103: return 0.0163122;  //g
	case 104: return 0.0355152;  //h
	case 105: return 0.0592608;  //i
	case 106: return 0.00165187; //j
	case 107: return 0.0037167;  //k
	case 108: return 0.0348957;  //l
	case 109: return 0.01879;    //m
	case 110: return 0.0569895;  //n
	case 111: return 0.0575057;  //o
	case 112: return 0.0169317;  //p
	case 113: return 0.000825934;//q
	case 114: return 0.053376;   //r
	case 115: return 0.050382;   //s
	case 116: return 0.0678299;  //t
	case 117: return 0.0245715;  //u
	case 118: return 0.00681396; //v
	case 119: return 0.00763989; //w
	case 120: return 0.00165187; //x
	case 121: return 0.0135247;  //y
	case 122: return 0.0012389;  //z
	default: return -1; //unused character
    }
    return 0;
}

