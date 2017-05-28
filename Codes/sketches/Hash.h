#ifndef _HASH_H
#define _HASH_H
#include "../includes.h"

class Hash
{
public: 
	Hash();
	~Hash();
	Hash(uint primeNum);
	void initialize(uint primeNum);
	u4 run(const char * str, uint len, int type);
	u4 BOBHash(const char * str, uint len);
private:
	uint primeNum;
};


u4 big_prime[MAX_BIG_PRIME] = {
	20177, 20183, 20201, 20219, 20231, 20233, 20249, 20261, 20269, 20287,
	20297, 20323, 20327, 20333, 20341, 20347, 20353, 20357, 20359, 20369,
	20389, 20393, 20399, 20407, 20411, 20431, 20441, 20443, 20477, 20479,
	20483, 20507, 20509, 20521, 20533, 20543, 20549, 20551, 20563, 20593,
	20599, 20611, 20627, 20639, 20641, 20663, 20681, 20693, 20707, 20717
};
u4 prime[MAX_PRIME] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
	547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
	661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
	739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
	811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
	947, 953, 967, 971, 977, 983, 991, 997,
	1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061,
	1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123,
	1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213,
	1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
	1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361,
	1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439,
	1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493,
	1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571,
	1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627,
	1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721,
	1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789,
	1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877,
	1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973,
	1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029,
	2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111,
	2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203,
	2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273,
	2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347,
	2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411,
	2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503,
	2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593,
	2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677,
	2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729,
	2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801,
	2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887,
	2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969,
	2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061,
	3067, 3079, 3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167,
	3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251,
	3253, 3257, 3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323,
	3329, 3331, 3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391,
	3407, 3413, 3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491,
	3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557,
	3559, 3571, 3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631,
	3637, 3643, 3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709,
	3719, 3727, 3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797,
	3803, 3821, 3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881,
	3889, 3907, 3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947,
	3967, 3989, 4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049,
	4051, 4057, 4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129,
	4133, 4139, 4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219,
	4229, 4231, 4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283,
	4289, 4297, 4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391,
	4397, 4409, 4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481,
	4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561,
	4567, 4583, 4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649,
	4651, 4657, 4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729,
	4733, 4751, 4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813,
	4817, 4831, 4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931,
	4933, 4937, 4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993,
	4999, 5003, 5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077,
	5081, 5087, 5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167,
	5171, 5179, 5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261,
	5273, 5279, 5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351,
	5381, 5387, 5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437,
	5441, 5443, 5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507,
	5519, 5521, 5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591,
	5623, 5639, 5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683,
	5689, 5693, 5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779,
	5783, 5791, 5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849,
	5851, 5857, 5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923,
	5927, 5939, 5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043,
	6047, 6053, 6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121,
	6131, 6133, 6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211,
	6217, 6221, 6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287,
	6299, 6301, 6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359,
	6361, 6367, 6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451,
	6469, 6473, 6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563,
	6569, 6571, 6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659,
	6661, 6673, 6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733,
	6737, 6761, 6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827,
	6829, 6833, 6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907,
	6911, 6917, 6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983,
	6991, 6997, 7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069,
	7079, 7103, 7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187,
	7193, 7207, 7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253,
	7283, 7297, 7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369,
	7393, 7411, 7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487,
	7489, 7499, 7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549,
	7559, 7561, 7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621,
	7639, 7643, 7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703,
	7717, 7723, 7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817,
	7823, 7829, 7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901,
	7907, 7919, 7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009,
	8011, 8017, 8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093,
	8101, 8111, 8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191,
	8209, 8219, 8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273,
	8287, 8291, 8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369,
	8377, 8387, 8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461,
	8467, 8501, 8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573,
	8581, 8597, 8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663,
	8669, 8677, 8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731,
	8737, 8741, 8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819,
	8821, 8831, 8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893,
	8923, 8929, 8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001,
	9007, 9011, 9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091,
	9103, 9109, 9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181,
	9187, 9199, 9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277,
	9281, 9283, 9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349,
	9371, 9377, 9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433,
	9437, 9439, 9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511,
	9521, 9533, 9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623,
	9629, 9631, 9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719,
	9721, 9733, 9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791,
	9803, 9811, 9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871,
	9883, 9887, 9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967,
	9973
};

#define mix(a,b,c) \
{ \
a=a-b;  a=a-c;  a=a^(c>>13); \
b=b-c;  b=b-a;  b=b^(a<<8);  \
c=c-a;  c=c-b;  c=c^(b>>13); \
a=a-b;  a=a-c;  a=a^(c>>12); \
b=b-c;  b=b-a;  b=b^(a<<16); \
c=c-a;  c=c-b;  c=c^(b>>5);  \
a=a-b;  a=a-c;  a=a^(c>>3);  \
b=b-c;  b=b-a;  b=b^(a<<10); \
c=c-a;  c=c-b;  c=c^(b>>15); \
}

Hash::Hash()
{
	this->primeNum = 0;
}

Hash::Hash(uint primeNum)
 {
	this->primeNum = primeNum % MAX_PRIME;
}

void Hash::initialize(uint primeNum)
 {
	this->primeNum = primeNum;
}

u4
OAAT(const char * str, uint len)
{
	u4   hash, i;
	for (hash=0, i=0; i<len; ++i)
	{
		hash += str[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

u4
Simple(const char * str, uint len)
{
    u4 hash = 0;
	for(uint i = 0; i < len; i++){
		hash = hash * 33 + str[i];
	}    
    return hash;
}

u4 
SBOX(const char * str, uint len)
{
	u4 box[]={
	0xF53E1837, 0x5F14C86B, 0x9EE3964C, 0xFA796D53, 0x32223FC3, 0x4D82BC98, 0xA0C7FA62, 0x63E2C982,
    0x24994A5B, 0x1ECE7BEE, 0x292B38EF, 0xD5CD4E56, 0x514F4303, 0x7BE12B83, 0x7192F195, 0x82DC7300,
    0x084380B4, 0x480B55D3, 0x5F430471, 0x13F75991, 0x3F9CF22C, 0x2FE0907A, 0xFD8E1E69, 0x7B1D5DE8,
    0xD575A85C, 0xAD01C50A, 0x7EE00737, 0x3CE981E8, 0x0E447EFA, 0x23089DD6, 0xB59F149F, 0x13600EC7,
    0xE802C8E6, 0x670921E4, 0x7207EFF0, 0xE74761B0, 0x69035234, 0xBFA40F19, 0xF63651A0, 0x29E64C26,
    0x1F98CCA7, 0xD957007E, 0xE71DDC75, 0x3E729595, 0x7580B7CC, 0xD7FAF60B, 0x92484323, 0xA44113EB,
    0xE4CBDE08, 0x346827C9, 0x3CF32AFA, 0x0B29BCF1, 0x6E29F7DF, 0xB01E71CB, 0x3BFBC0D1, 0x62EDC5B8,
    0xB7DE789A, 0xA4748EC9, 0xE17A4C4F, 0x67E5BD03, 0xF3B33D1A, 0x97D8D3E9, 0x09121BC0, 0x347B2D2C,
    0x79A1913C, 0x504172DE, 0x7F1F8483, 0x13AC3CF6, 0x7A2094DB, 0xC778FA12, 0xADF7469F, 0x21786B7B,
    0x71A445D0, 0xA8896C1B, 0x656F62FB, 0x83A059B3, 0x972DFE6E, 0x4122000C, 0x97D9DA19, 0x17D5947B,
    0xB1AFFD0C, 0x6EF83B97, 0xAF7F780B, 0x4613138A, 0x7C3E73A6, 0xCF15E03D, 0x41576322, 0x672DF292,
    0xB658588D, 0x33EBEFA9, 0x938CBF06, 0x06B67381, 0x07F192C6, 0x2BDA5855, 0x348EE0E8, 0x19DBB6E3,
    0x3222184B, 0xB69D5DBA, 0x7E760B88, 0xAF4D8154, 0x007A51AD, 0x35112500, 0xC9CD2D7D, 0x4F4FB761,
    0x694772E3, 0x694C8351, 0x4A7E3AF5, 0x67D65CE1, 0x9287DE92, 0x2518DB3C, 0x8CB4EC06, 0xD154D38F,
    0xE19A26BB, 0x295EE439, 0xC50A1104, 0x2153C6A7, 0x82366656, 0x0713BC2F, 0x6462215A, 0x21D9BFCE,
    0xBA8EACE6, 0xAE2DF4C1, 0x2A8D5E80, 0x3F7E52D1, 0x29359399, 0xFEA1D19C, 0x18879313, 0x455AFA81,
    0xFADFE838, 0x62609838, 0xD1028839, 0x0736E92F, 0x3BCA22A3, 0x1485B08A, 0x2DA7900B, 0x852C156D,
    0xE8F24803, 0x00078472, 0x13F0D332, 0x2ACFD0CF, 0x5F747F5C, 0x87BB1E2F, 0xA7EFCB63, 0x23F432F0,
    0xE6CE7C5C, 0x1F954EF6, 0xB609C91B, 0x3B4571BF, 0xEED17DC0, 0xE556CDA0, 0xA7846A8D, 0xFF105F94,
    0x52B7CCDE, 0x0E33E801, 0x664455EA, 0xF2C70414, 0x73E7B486, 0x8F830661, 0x8B59E826, 0xBB8AEDCA,
    0xF3D70AB9, 0xD739F2B9, 0x4A04C34A, 0x88D0F089, 0xE02191A2, 0xD89D9C78, 0x192C2749, 0xFC43A78F,
    0x0AAC88CB, 0x9438D42D, 0x9E280F7A, 0x36063802, 0x38E8D018, 0x1C42A9CB, 0x92AAFF6C, 0xA24820C5,
    0x007F077F, 0xCE5BC543, 0x69668D58, 0x10D6FF74, 0xBE00F621, 0x21300BBE, 0x2E9E8F46, 0x5ACEA629,
    0xFA1F86C7, 0x52F206B8, 0x3EDF1A75, 0x6DA8D843, 0xCF719928, 0x73E3891F, 0xB4B95DD6, 0xB2A42D27,
    0xEDA20BBF, 0x1A58DBDF, 0xA449AD03, 0x6DDEF22B, 0x900531E6, 0x3D3BFF35, 0x5B24ABA2, 0x472B3E4C,
    0x387F2D75, 0x4D8DBA36, 0x71CB5641, 0xE3473F3F, 0xF6CD4B7F, 0xBF7D1428, 0x344B64D0, 0xC5CDFCB6,
    0xFE2E0182, 0x2C37A673, 0xDE4EB7A3, 0x63FDC933, 0x01DC4063, 0x611F3571, 0xD167BFAF, 0x4496596F,
    0x3DEE0689, 0xD8704910, 0x7052A114, 0x068C9EC5, 0x75D0E766, 0x4D54CC20, 0xB44ECDE2, 0x4ABC653E,
    0x2C550A21, 0x1A52C0DB, 0xCFED03D0, 0x119BAFE2, 0x876A6133, 0xBC232088, 0x435BA1B2, 0xAE99BBFA,
    0xBB4F08E4, 0xA62B5F49, 0x1DA4B695, 0x336B84DE, 0xDC813D31, 0x00C134FB, 0x397A98E6, 0x151F0E64,
    0xD9EB3E69, 0xD3C7DF60, 0xD2F2C336, 0x2DDD067B, 0xBD122835, 0xB0B3BD3A, 0xB0D54E46, 0x8641F1E4,
    0xA0B38F96, 0x51D39199, 0x37A6AD75, 0xDF84EE41, 0x3C034CBA, 0xACDA62FC, 0x11923B8B, 0x45EF170A
	};
	u4 hash = 0;
	for(uint i = 0; i < len; i++){
		hash ^= box[str[i]];
		hash *= 3;
	}
	return hash;
}
#include <stdint.h>
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

u4
Hsieh (const char * str, unsigned int len)
{
	u4 hash = len, tmp;
	int rem;

    //if (len <= 0 || str == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (str);
        tmp    = (get16bits (str+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        str  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (str);
                hash ^= hash << 16;
                hash ^= ((signed char)str[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (str);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*str;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

u4 
RSHash(const char * str, unsigned int len)
{
    u4 b = 378551;
    u4 a = 63689;
    u4 hash = 0;
	
	for(uint i = 0; i < len; i++){
		hash = hash * a + (*str++);
        a *= b;
	}
    //return (hash & 0x7FFFFFFF);
	return hash;
}

u4 
JSHash(const char * str, unsigned int len)
{
	u4 hash = 1315423911;  
	for(uint i = 0; i < len; i++)  
	{  
		hash ^= ((hash << 5) + str[i] + (hash >> 2));  
	}  
	return hash;
}

u4 
BKDR(const char * str, unsigned int len)
{	
	u4 seed = 131; // 31 131 1313 13131 131313 etc..  
    u4 hash = 0;  
	for(uint i = 0; i < len; i++)  
	{  
		hash = (hash * seed) + str[i]; 
	}
	
	return hash;
}

u4 
DJBHash (const char * str, unsigned int len)
{
    u4 hash = 5381;
	for(uint i = 0; i < len; i++){
		hash += (hash << 5) + (*str++);
	}
    //return (hash & 0x7FFFFFFF);
	return hash;
}

u4 
DEKHash(const char * str, unsigned int len)   
{   
    
    u4 hash = 1315423911;
	for(uint i = 0; i < len; i++){
		hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
	}
	
    return hash;
}

// AP Hash 
u4 
APHash(const char *str, unsigned int len)
{
	u4 hash = 0;
	
 
	for (uint i = 0; i < len; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}
 
	//return (hash & 0x7FFFFFFF);
	return hash;
}

u4 
CRC32(const char * str,unsigned int len)
{  
	u4 crctab[256] =
	{
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3, 
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5, 
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F, 
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433, 
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01, 
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB, 
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F, 
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD, 
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7, 
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79, 
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713, 
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45, 
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, 
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF, 
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
	};
    u4 hash;     

    hash=0xffffffff;
    for(uint i = 0; i < len; i++){
        hash = (hash >> 8) ^ crctab[(hash & 0xFF) ^ str[i]];     
    }  
    
    hash ^= 0xFFFFFFFF;  
    return hash;     
}

u4
SDBM(const char *str, unsigned int len)
{
	u4 hash = 0;
	
	for (uint i=0; i<len; i++) {
		hash = str[i] + (hash << 6) + (hash << 16) - hash;
	}
	
	return hash;
}

u4
OCaml(const char *str, unsigned int len) 
{
	u4 hash = 0;

	for (uint i=0; i<len; i++) {
		hash = hash*19 + str[i];
	}

	return hash;
}

u4
SML(const char *str, unsigned int len)
{
	u4 hash = 0;

	for (uint i=0; i<len; i++) 
	{
		hash = 33*hash + 720 + str[i];
	}

	return hash;
}

u4
STL(const char *str, unsigned int len) 
{
	u4 hash = 0;

	for (uint i=0; i<len; i++) 
	{
		hash = 5*hash + str[i];
	}

	return hash;
}



u4
FNV32(const char *str, unsigned int len)
{
    //char *bp = (char *)str;	/* start of buffer */
    //char *be = str + len;		/* beyond end of buffer */
	u4 hval = 0;
    for(uint i = 0; i < len; i++) {
		hval *= 0x01000193;

		//hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
		
		/* xor the bottom with the current octet */
		hval ^= (u4)*str++;
    }

    /* return our new hash value */
    return hval;
}

// P. J. Weinberger Hash Function
u4
PJWHash (const char *str, unsigned int len)
{
    u4 BitsInUnignedInt = (u4) (sizeof (unsigned
							    int) * 8);
    u4 ThreeQuarters = (u4) ((BitsInUnignedInt * 3) / 4);
    u4 OneEighth = (u4) (BitsInUnignedInt / 8);
    u4 HighBits = (u4) (0xFFFFFFFF) <<
	(BitsInUnignedInt - OneEighth);
    u4 hash = 0;
    u4 test = 0;
    for(uint i = 0; i < len; i++)
    {
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}
    return hash ;
}


u4 Hash::BOBHash(const char * k, uint len)
{
	//register ub4 a,b,c,len;
	u4 a,b,c;
	/* Set up the internal state */
	//len = length;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */

	c = prime[this->primeNum];		 /* the previous hash value */

	/*---------------------------------------- handle most of the key */

    while (len >= 12)
    {
        a=a+(k[0]+((u4)k[1]<<8)+((u4)k[2]<<16) +((u4)k[3]<<24));
        b=b+(k[4]+((u4)k[5]<<8)+((u4)k[6]<<16) +((u4)k[7]<<24));
        c=c+(k[8]+((u4)k[9]<<8)+((u4)k[10]<<16)+((u4)k[11]<<24));
        mix(a,b,c);
        k = k+12; len = len-12;
    }

	/*------------------------------------- handle the last 11 bytes */
	c += len;
    switch(len)              /* all the case statements fall through */
    {
        case 11: c=c+((u4)k[10]<<24);
        case 10: c=c+((u4)k[9]<<16);
        case 9 : c=c+((u4)k[8]<<8);
            /* the first byte of c is reserved for the length */
        case 8 : b=b+((u4)k[7]<<24);
        case 7 : b=b+((u4)k[6]<<16);
        case 6 : b=b+((u4)k[5]<<8);
        case 5 : b=b+k[4];
        case 4 : a=a+((u4)k[3]<<24);
        case 3 : a=a+((u4)k[2]<<16);
        case 2 : a=a+((u4)k[1]<<8);
        case 1 : a=a+k[0];
            /* case 0: nothing left to add */
    }
    mix(a,b,c);
    /*-------------------------------------------- report the result */
    return c;
}

u4 Hash::run(const char * str, uint len, int type) {
	switch(type)
	{
		case 0: return BOBHash(str, len);
		case 1: return OAAT(str, len);
		case 2: return Simple(str, len);
		case 3: return SBOX(str, len);
		case 4: return Hsieh(str, len);
		case 5: return RSHash(str, len);
		case 6: return JSHash(str, len);
		case 7: return BKDR(str, len);
		case 8: return DJBHash(str, len);
		case 9: return DEKHash(str, len);
		case 10: return APHash(str, len);
		case 11: return CRC32(str, len);
		case 12: return SDBM(str, len);
		case 13: return OCaml(str, len);
		case 14: return SML(str, len);
		case 15: return STL(str, len);
		case 16: return FNV32(str, len);
		case 17: return PJWHash(str, len);
	}
	return 0;
}

Hash::~Hash()
{

}
#endif //_BOBHASH_H
