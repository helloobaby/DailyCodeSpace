
#define log(...) printf(__VA_ARGS__)
#define mem_malloc(...) malloc(__VA_ARGS__)

// 数据集数量
int data_size = 135;
// 测试集数量
int test_data_size = 15;

// 花的三种类别
// 分别对应Iris-setosa,Iris-versicolor,Iris-virginica
enum classfy {
	A,B,C
};


struct Iris {
  double feature[4];
  enum classfy label;
};

// 计算距离
double computedistance(int n1, int n2,struct Iris* data,struct Iris* test_data) {
	double sum = 0.0;
	int i;
	for (i = 0; i < 4; i++) {
		sum += pow(data[n1].feature[i] - test_data[n2].feature[i], 2.0);
	}
	return sqrt(sum);
}

struct Iris* create_data_set() {
  struct Iris* data = mem_malloc(data_size * sizeof(struct Iris));
  data[0].feature[0] = 5.1;
  data[0].feature[1] = 3.5;
  data[0].feature[2] = 1.4;
  data[0].feature[3] = 0.2;
  data[0].label = A;
  data[1].feature[0] = 4.9;
  data[1].feature[1] = 3.0;
  data[1].feature[2] = 1.4;
  data[1].feature[3] = 0.2;
  data[1].label = A;
  data[2].feature[0] = 4.7;
  data[2].feature[1] = 3.2;
  data[2].feature[2] = 1.3;
  data[2].feature[3] = 0.2;
  data[2].label = A;
  data[3].feature[0] = 4.6;
  data[3].feature[1] = 3.1;
  data[3].feature[2] = 1.5;
  data[3].feature[3] = 0.2;
  data[3].label = A;
  data[4].feature[0] = 5.0;
  data[4].feature[1] = 3.6;
  data[4].feature[2] = 1.4;
  data[4].feature[3] = 0.2;
  data[4].label = A;
  data[5].feature[0] = 5.4;
  data[5].feature[1] = 3.9;
  data[5].feature[2] = 1.7;
  data[5].feature[3] = 0.4;
  data[5].label = A;
  data[6].feature[0] = 4.6;
  data[6].feature[1] = 3.4;
  data[6].feature[2] = 1.4;
  data[6].feature[3] = 0.3;
  data[6].label = A;
  data[7].feature[0] = 5.0;
  data[7].feature[1] = 3.4;
  data[7].feature[2] = 1.5;
  data[7].feature[3] = 0.2;
  data[7].label = A;
  data[8].feature[0] = 4.4;
  data[8].feature[1] = 2.9;
  data[8].feature[2] = 1.4;
  data[8].feature[3] = 0.2;
  data[8].label = A;
  data[9].feature[0] = 4.9;
  data[9].feature[1] = 3.1;
  data[9].feature[2] = 1.5;
  data[9].feature[3] = 0.1;
  data[9].label = A;
  data[10].feature[0] = 5.4;
  data[10].feature[1] = 3.7;
  data[10].feature[2] = 1.5;
  data[10].feature[3] = 0.2;
  data[10].label = A;
  data[11].feature[0] = 4.8;
  data[11].feature[1] = 3.4;
  data[11].feature[2] = 1.6;
  data[11].feature[3] = 0.2;
  data[11].label = A;
  data[12].feature[0] = 4.8;
  data[12].feature[1] = 3.0;
  data[12].feature[2] = 1.4;
  data[12].feature[3] = 0.1;
  data[12].label = A;
  data[13].feature[0] = 4.3;
  data[13].feature[1] = 3.0;
  data[13].feature[2] = 1.1;
  data[13].feature[3] = 0.1;
  data[13].label = A;
  data[14].feature[0] = 5.8;
  data[14].feature[1] = 4.0;
  data[14].feature[2] = 1.2;
  data[14].feature[3] = 0.2;
  data[14].label = A;
  data[15].feature[0] = 5.7;
  data[15].feature[1] = 4.4;
  data[15].feature[2] = 1.5;
  data[15].feature[3] = 0.4;
  data[15].label = A;
  data[16].feature[0] = 5.4;
  data[16].feature[1] = 3.9;
  data[16].feature[2] = 1.3;
  data[16].feature[3] = 0.4;
  data[16].label = A;
  data[17].feature[0] = 5.1;
  data[17].feature[1] = 3.5;
  data[17].feature[2] = 1.4;
  data[17].feature[3] = 0.3;
  data[17].label = A;
  data[18].feature[0] = 5.7;
  data[18].feature[1] = 3.8;
  data[18].feature[2] = 1.7;
  data[18].feature[3] = 0.3;
  data[18].label = A;
  data[19].feature[0] = 5.1;
  data[19].feature[1] = 3.8;
  data[19].feature[2] = 1.5;
  data[19].feature[3] = 0.3;
  data[19].label = A;
  data[20].feature[0] = 5.4;
  data[20].feature[1] = 3.4;
  data[20].feature[2] = 1.7;
  data[20].feature[3] = 0.2;
  data[20].label = A;
  data[21].feature[0] = 5.1;
  data[21].feature[1] = 3.7;
  data[21].feature[2] = 1.5;
  data[21].feature[3] = 0.4;
  data[21].label = A;
  data[22].feature[0] = 4.6;
  data[22].feature[1] = 3.6;
  data[22].feature[2] = 1.0;
  data[22].feature[3] = 0.2;
  data[22].label = A;
  data[23].feature[0] = 5.1;
  data[23].feature[1] = 3.3;
  data[23].feature[2] = 1.7;
  data[23].feature[3] = 0.5;
  data[23].label = A;
  data[24].feature[0] = 4.8;
  data[24].feature[1] = 3.4;
  data[24].feature[2] = 1.9;
  data[24].feature[3] = 0.2;
  data[24].label = A;
  data[25].feature[0] = 5.0;
  data[25].feature[1] = 3.0;
  data[25].feature[2] = 1.6;
  data[25].feature[3] = 0.2;
  data[25].label = A;
  data[26].feature[0] = 5.0;
  data[26].feature[1] = 3.4;
  data[26].feature[2] = 1.6;
  data[26].feature[3] = 0.4;
  data[26].label = A;
  data[27].feature[0] = 5.2;
  data[27].feature[1] = 3.5;
  data[27].feature[2] = 1.5;
  data[27].feature[3] = 0.2;
  data[27].label = A;
  data[28].feature[0] = 5.2;
  data[28].feature[1] = 3.4;
  data[28].feature[2] = 1.4;
  data[28].feature[3] = 0.2;
  data[28].label = A;
  data[29].feature[0] = 4.7;
  data[29].feature[1] = 3.2;
  data[29].feature[2] = 1.6;
  data[29].feature[3] = 0.2;
  data[29].label = A;
  data[30].feature[0] = 4.8;
  data[30].feature[1] = 3.1;
  data[30].feature[2] = 1.6;
  data[30].feature[3] = 0.2;
  data[30].label = A;
  data[31].feature[0] = 5.4;
  data[31].feature[1] = 3.4;
  data[31].feature[2] = 1.5;
  data[31].feature[3] = 0.4;
  data[31].label = A;
  data[32].feature[0] = 5.2;
  data[32].feature[1] = 4.1;
  data[32].feature[2] = 1.5;
  data[32].feature[3] = 0.1;
  data[32].label = A;
  data[33].feature[0] = 5.5;
  data[33].feature[1] = 4.2;
  data[33].feature[2] = 1.4;
  data[33].feature[3] = 0.2;
  data[33].label = A;
  data[34].feature[0] = 4.9;
  data[34].feature[1] = 3.1;
  data[34].feature[2] = 1.5;
  data[34].feature[3] = 0.1;
  data[34].label = A;
  data[35].feature[0] = 5.0;
  data[35].feature[1] = 3.2;
  data[35].feature[2] = 1.2;
  data[35].feature[3] = 0.2;
  data[35].label = A;
  data[36].feature[0] = 5.5;
  data[36].feature[1] = 3.5;
  data[36].feature[2] = 1.3;
  data[36].feature[3] = 0.2;
  data[36].label = A;
  data[37].feature[0] = 4.9;
  data[37].feature[1] = 3.1;
  data[37].feature[2] = 1.5;
  data[37].feature[3] = 0.1;
  data[37].label = A;
  data[38].feature[0] = 4.4;
  data[38].feature[1] = 3.0;
  data[38].feature[2] = 1.3;
  data[38].feature[3] = 0.2;
  data[38].label = A;
  data[39].feature[0] = 5.1;
  data[39].feature[1] = 3.4;
  data[39].feature[2] = 1.5;
  data[39].feature[3] = 0.2;
  data[39].label = A;
  data[40].feature[0] = 5.0;
  data[40].feature[1] = 3.5;
  data[40].feature[2] = 1.3;
  data[40].feature[3] = 0.3;
  data[40].label = A;
  data[41].feature[0] = 4.5;
  data[41].feature[1] = 2.3;
  data[41].feature[2] = 1.3;
  data[41].feature[3] = 0.3;
  data[41].label = A;
  data[42].feature[0] = 4.4;
  data[42].feature[1] = 3.2;
  data[42].feature[2] = 1.3;
  data[42].feature[3] = 0.2;
  data[42].label = A;
  data[43].feature[0] = 5.0;
  data[43].feature[1] = 3.5;
  data[43].feature[2] = 1.6;
  data[43].feature[3] = 0.6;
  data[43].label = A;
  data[44].feature[0] = 5.1;
  data[44].feature[1] = 3.8;
  data[44].feature[2] = 1.9;
  data[44].feature[3] = 0.4;
  data[44].label = A;
  data[45].feature[0] = 7.0;
  data[45].feature[1] = 3.2;
  data[45].feature[2] = 4.7;
  data[45].feature[3] = 1.4;
  data[45].label = B;
  data[46].feature[0] = 6.4;
  data[46].feature[1] = 3.2;
  data[46].feature[2] = 4.5;
  data[46].feature[3] = 1.5;
  data[46].label = B;
  data[47].feature[0] = 6.9;
  data[47].feature[1] = 3.1;
  data[47].feature[2] = 4.9;
  data[47].feature[3] = 1.5;
  data[47].label = B;
  data[48].feature[0] = 5.5;
  data[48].feature[1] = 2.3;
  data[48].feature[2] = 4.0;
  data[48].feature[3] = 1.3;
  data[48].label = B;
  data[49].feature[0] = 6.5;
  data[49].feature[1] = 2.8;
  data[49].feature[2] = 4.6;
  data[49].feature[3] = 1.5;
  data[49].label = B;
  data[50].feature[0] = 5.7;
  data[50].feature[1] = 2.8;
  data[50].feature[2] = 4.5;
  data[50].feature[3] = 1.3;
  data[50].label = B;
  data[51].feature[0] = 6.3;
  data[51].feature[1] = 3.3;
  data[51].feature[2] = 4.7;
  data[51].feature[3] = 1.6;
  data[51].label = B;
  data[52].feature[0] = 4.9;
  data[52].feature[1] = 2.4;
  data[52].feature[2] = 3.3;
  data[52].feature[3] = 1.0;
  data[52].label = B;
  data[53].feature[0] = 6.6;
  data[53].feature[1] = 2.9;
  data[53].feature[2] = 4.6;
  data[53].feature[3] = 1.3;
  data[53].label = B;
  data[54].feature[0] = 5.2;
  data[54].feature[1] = 2.7;
  data[54].feature[2] = 3.9;
  data[54].feature[3] = 1.4;
  data[54].label = B;
  data[55].feature[0] = 5.0;
  data[55].feature[1] = 2.0;
  data[55].feature[2] = 3.5;
  data[55].feature[3] = 1.0;
  data[55].label = B;
  data[56].feature[0] = 5.9;
  data[56].feature[1] = 3.0;
  data[56].feature[2] = 4.2;
  data[56].feature[3] = 1.5;
  data[56].label = B;
  data[57].feature[0] = 6.0;
  data[57].feature[1] = 2.2;
  data[57].feature[2] = 4.0;
  data[57].feature[3] = 1.0;
  data[57].label = B;
  data[58].feature[0] = 6.1;
  data[58].feature[1] = 2.9;
  data[58].feature[2] = 4.7;
  data[58].feature[3] = 1.4;
  data[58].label = B;
  data[59].feature[0] = 5.6;
  data[59].feature[1] = 2.9;
  data[59].feature[2] = 3.6;
  data[59].feature[3] = 1.3;
  data[59].label = B;
  data[60].feature[0] = 6.7;
  data[60].feature[1] = 3.1;
  data[60].feature[2] = 4.4;
  data[60].feature[3] = 1.4;
  data[60].label = B;
  data[61].feature[0] = 5.6;
  data[61].feature[1] = 3.0;
  data[61].feature[2] = 4.5;
  data[61].feature[3] = 1.5;
  data[61].label = B;
  data[62].feature[0] = 5.8;
  data[62].feature[1] = 2.7;
  data[62].feature[2] = 4.1;
  data[62].feature[3] = 1.0;
  data[62].label = B;
  data[63].feature[0] = 6.2;
  data[63].feature[1] = 2.2;
  data[63].feature[2] = 4.5;
  data[63].feature[3] = 1.5;
  data[63].label = B;
  data[64].feature[0] = 5.6;
  data[64].feature[1] = 2.5;
  data[64].feature[2] = 3.9;
  data[64].feature[3] = 1.1;
  data[64].label = B;
  data[65].feature[0] = 5.9;
  data[65].feature[1] = 3.2;
  data[65].feature[2] = 4.8;
  data[65].feature[3] = 1.8;
  data[65].label = B;
  data[66].feature[0] = 6.1;
  data[66].feature[1] = 2.8;
  data[66].feature[2] = 4.0;
  data[66].feature[3] = 1.3;
  data[66].label = B;
  data[67].feature[0] = 6.3;
  data[67].feature[1] = 2.5;
  data[67].feature[2] = 4.9;
  data[67].feature[3] = 1.5;
  data[67].label = B;
  data[68].feature[0] = 6.1;
  data[68].feature[1] = 2.8;
  data[68].feature[2] = 4.7;
  data[68].feature[3] = 1.2;
  data[68].label = B;
  data[69].feature[0] = 6.4;
  data[69].feature[1] = 2.9;
  data[69].feature[2] = 4.3;
  data[69].feature[3] = 1.3;
  data[69].label = B;
  data[70].feature[0] = 6.6;
  data[70].feature[1] = 3.0;
  data[70].feature[2] = 4.4;
  data[70].feature[3] = 1.4;
  data[70].label = B;
  data[71].feature[0] = 6.8;
  data[71].feature[1] = 2.8;
  data[71].feature[2] = 4.8;
  data[71].feature[3] = 1.4;
  data[71].label = B;
  data[72].feature[0] = 6.7;
  data[72].feature[1] = 3.0;
  data[72].feature[2] = 5.0;
  data[72].feature[3] = 1.7;
  data[72].label = B;
  data[73].feature[0] = 6.0;
  data[73].feature[1] = 2.9;
  data[73].feature[2] = 4.5;
  data[73].feature[3] = 1.5;
  data[73].label = B;
  data[74].feature[0] = 5.7;
  data[74].feature[1] = 2.6;
  data[74].feature[2] = 3.5;
  data[74].feature[3] = 1.0;
  data[74].label = B;
  data[75].feature[0] = 5.5;
  data[75].feature[1] = 2.4;
  data[75].feature[2] = 3.8;
  data[75].feature[3] = 1.1;
  data[75].label = B;
  data[76].feature[0] = 5.5;
  data[76].feature[1] = 2.4;
  data[76].feature[2] = 3.7;
  data[76].feature[3] = 1.0;
  data[76].label = B;
  data[77].feature[0] = 5.8;
  data[77].feature[1] = 2.7;
  data[77].feature[2] = 3.9;
  data[77].feature[3] = 1.2;
  data[77].label = B;
  data[78].feature[0] = 6.0;
  data[78].feature[1] = 2.7;
  data[78].feature[2] = 5.1;
  data[78].feature[3] = 1.6;
  data[78].label = B;
  data[79].feature[0] = 5.4;
  data[79].feature[1] = 3.0;
  data[79].feature[2] = 4.5;
  data[79].feature[3] = 1.5;
  data[79].label = B;
  data[80].feature[0] = 6.0;
  data[80].feature[1] = 3.4;
  data[80].feature[2] = 4.5;
  data[80].feature[3] = 1.6;
  data[80].label = B;
  data[81].feature[0] = 6.7;
  data[81].feature[1] = 3.1;
  data[81].feature[2] = 4.7;
  data[81].feature[3] = 1.5;
  data[81].label = B;
  data[82].feature[0] = 6.3;
  data[82].feature[1] = 2.3;
  data[82].feature[2] = 4.4;
  data[82].feature[3] = 1.3;
  data[82].label = B;
  data[83].feature[0] = 5.6;
  data[83].feature[1] = 3.0;
  data[83].feature[2] = 4.1;
  data[83].feature[3] = 1.3;
  data[83].label = B;
  data[84].feature[0] = 5.5;
  data[84].feature[1] = 2.5;
  data[84].feature[2] = 4.0;
  data[84].feature[3] = 1.3;
  data[84].label = B;
  data[85].feature[0] = 5.5;
  data[85].feature[1] = 2.6;
  data[85].feature[2] = 4.4;
  data[85].feature[3] = 1.2;
  data[85].label = B;
  data[86].feature[0] = 6.1;
  data[86].feature[1] = 3.0;
  data[86].feature[2] = 4.6;
  data[86].feature[3] = 1.4;
  data[86].label = B;
  data[87].feature[0] = 5.8;
  data[87].feature[1] = 2.6;
  data[87].feature[2] = 4.0;
  data[87].feature[3] = 1.2;
  data[87].label = B;
  data[88].feature[0] = 5.0;
  data[88].feature[1] = 2.3;
  data[88].feature[2] = 3.3;
  data[88].feature[3] = 1.0;
  data[88].label = B;
  data[89].feature[0] = 5.6;
  data[89].feature[1] = 2.7;
  data[89].feature[2] = 4.2;
  data[89].feature[3] = 1.3;
  data[89].label = B;
  data[90].feature[0] = 6.3;
  data[90].feature[1] = 3.3;
  data[90].feature[2] = 6.0;
  data[90].feature[3] = 2.5;
  data[90].label = C;
  data[91].feature[0] = 5.8;
  data[91].feature[1] = 2.7;
  data[91].feature[2] = 5.1;
  data[91].feature[3] = 1.9;
  data[91].label = C;
  data[92].feature[0] = 7.1;
  data[92].feature[1] = 3.0;
  data[92].feature[2] = 5.9;
  data[92].feature[3] = 2.1;
  data[92].label = C;
  data[93].feature[0] = 6.3;
  data[93].feature[1] = 2.9;
  data[93].feature[2] = 5.6;
  data[93].feature[3] = 1.8;
  data[93].label = C;
  data[94].feature[0] = 6.5;
  data[94].feature[1] = 3.0;
  data[94].feature[2] = 5.8;
  data[94].feature[3] = 2.2;
  data[94].label = C;
  data[95].feature[0] = 7.6;
  data[95].feature[1] = 3.0;
  data[95].feature[2] = 6.6;
  data[95].feature[3] = 2.1;
  data[95].label = C;
  data[96].feature[0] = 4.9;
  data[96].feature[1] = 2.5;
  data[96].feature[2] = 4.5;
  data[96].feature[3] = 1.7;
  data[96].label = C;
  data[97].feature[0] = 7.3;
  data[97].feature[1] = 2.9;
  data[97].feature[2] = 6.3;
  data[97].feature[3] = 1.8;
  data[97].label = C;
  data[98].feature[0] = 6.7;
  data[98].feature[1] = 2.5;
  data[98].feature[2] = 5.8;
  data[98].feature[3] = 1.8;
  data[98].label = C;
  data[99].feature[0] = 7.2;
  data[99].feature[1] = 3.6;
  data[99].feature[2] = 6.1;
  data[99].feature[3] = 2.5;
  data[99].label = C;
  data[100].feature[0] = 6.5;
  data[100].feature[1] = 3.2;
  data[100].feature[2] = 5.1;
  data[100].feature[3] = 2.0;
  data[100].label = C;
  data[101].feature[0] = 6.4;
  data[101].feature[1] = 2.7;
  data[101].feature[2] = 5.3;
  data[101].feature[3] = 1.9;
  data[101].label = C;
  data[102].feature[0] = 6.8;
  data[102].feature[1] = 3.0;
  data[102].feature[2] = 5.5;
  data[102].feature[3] = 2.1;
  data[102].label = C;
  data[103].feature[0] = 5.7;
  data[103].feature[1] = 2.5;
  data[103].feature[2] = 5.0;
  data[103].feature[3] = 2.0;
  data[103].label = C;
  data[104].feature[0] = 5.8;
  data[104].feature[1] = 2.8;
  data[104].feature[2] = 5.1;
  data[104].feature[3] = 2.4;
  data[104].label = C;
  data[105].feature[0] = 6.4;
  data[105].feature[1] = 3.2;
  data[105].feature[2] = 5.3;
  data[105].feature[3] = 2.3;
  data[105].label = C;
  data[106].feature[0] = 6.5;
  data[106].feature[1] = 3.0;
  data[106].feature[2] = 5.5;
  data[106].feature[3] = 1.8;
  data[106].label = C;
  data[107].feature[0] = 7.7;
  data[107].feature[1] = 3.8;
  data[107].feature[2] = 6.7;
  data[107].feature[3] = 2.2;
  data[107].label = C;
  data[108].feature[0] = 7.7;
  data[108].feature[1] = 2.6;
  data[108].feature[2] = 6.9;
  data[108].feature[3] = 2.3;
  data[108].label = C;
  data[109].feature[0] = 6.0;
  data[109].feature[1] = 2.2;
  data[109].feature[2] = 5.0;
  data[109].feature[3] = 1.5;
  data[109].label = C;
  data[110].feature[0] = 6.9;
  data[110].feature[1] = 3.2;
  data[110].feature[2] = 5.7;
  data[110].feature[3] = 2.3;
  data[110].label = C;
  data[111].feature[0] = 5.6;
  data[111].feature[1] = 2.8;
  data[111].feature[2] = 4.9;
  data[111].feature[3] = 2.0;
  data[111].label = C;
  data[112].feature[0] = 7.7;
  data[112].feature[1] = 2.8;
  data[112].feature[2] = 6.7;
  data[112].feature[3] = 2.0;
  data[112].label = C;
  data[113].feature[0] = 6.3;
  data[113].feature[1] = 2.7;
  data[113].feature[2] = 4.9;
  data[113].feature[3] = 1.8;
  data[113].label = C;
  data[114].feature[0] = 6.7;
  data[114].feature[1] = 3.3;
  data[114].feature[2] = 5.7;
  data[114].feature[3] = 2.1;
  data[114].label = C;
  data[115].feature[0] = 7.2;
  data[115].feature[1] = 3.2;
  data[115].feature[2] = 6.0;
  data[115].feature[3] = 1.8;
  data[115].label = C;
  data[116].feature[0] = 6.2;
  data[116].feature[1] = 2.8;
  data[116].feature[2] = 4.8;
  data[116].feature[3] = 1.8;
  data[116].label = C;
  data[117].feature[0] = 6.1;
  data[117].feature[1] = 3.0;
  data[117].feature[2] = 4.9;
  data[117].feature[3] = 1.8;
  data[117].label = C;
  data[118].feature[0] = 6.4;
  data[118].feature[1] = 2.8;
  data[118].feature[2] = 5.6;
  data[118].feature[3] = 2.1;
  data[118].label = C;
  data[119].feature[0] = 7.2;
  data[119].feature[1] = 3.0;
  data[119].feature[2] = 5.8;
  data[119].feature[3] = 1.6;
  data[119].label = C;
  data[120].feature[0] = 7.4;
  data[120].feature[1] = 2.8;
  data[120].feature[2] = 6.1;
  data[120].feature[3] = 1.9;
  data[120].label = C;
  data[121].feature[0] = 7.9;
  data[121].feature[1] = 3.8;
  data[121].feature[2] = 6.4;
  data[121].feature[3] = 2.0;
  data[121].label = C;
  data[122].feature[0] = 6.4;
  data[122].feature[1] = 2.8;
  data[122].feature[2] = 5.6;
  data[122].feature[3] = 2.2;
  data[122].label = C;
  data[123].feature[0] = 6.3;
  data[123].feature[1] = 2.8;
  data[123].feature[2] = 5.1;
  data[123].feature[3] = 1.5;
  data[123].label = C;
  data[124].feature[0] = 6.1;
  data[124].feature[1] = 2.6;
  data[124].feature[2] = 5.6;
  data[124].feature[3] = 1.4;
  data[124].label = C;
  data[125].feature[0] = 7.7;
  data[125].feature[1] = 3.0;
  data[125].feature[2] = 6.1;
  data[125].feature[3] = 2.3;
  data[125].label = C;
  data[126].feature[0] = 6.3;
  data[126].feature[1] = 3.4;
  data[126].feature[2] = 5.6;
  data[126].feature[3] = 2.4;
  data[126].label = C;
  data[127].feature[0] = 6.4;
  data[127].feature[1] = 3.1;
  data[127].feature[2] = 5.5;
  data[127].feature[3] = 1.8;
  data[127].label = C;
  data[128].feature[0] = 6.0;
  data[128].feature[1] = 3.0;
  data[128].feature[2] = 4.8;
  data[128].feature[3] = 1.8;
  data[128].label = C;
  data[129].feature[0] = 6.9;
  data[129].feature[1] = 3.1;
  data[129].feature[2] = 5.4;
  data[129].feature[3] = 2.1;
  data[129].label = C;
  data[130].feature[0] = 6.7;
  data[130].feature[1] = 3.1;
  data[130].feature[2] = 5.6;
  data[130].feature[3] = 2.4;
  data[130].label = C;
  data[131].feature[0] = 6.9;
  data[131].feature[1] = 3.1;
  data[131].feature[2] = 5.1;
  data[131].feature[3] = 2.3;
  data[131].label = C;
  data[132].feature[0] = 5.8;
  data[132].feature[1] = 2.7;
  data[132].feature[2] = 5.1;
  data[132].feature[3] = 1.9;
  data[132].label = C;
  data[133].feature[0] = 6.8;
  data[133].feature[1] = 3.2;
  data[133].feature[2] = 5.9;
  data[133].feature[3] = 2.3;
  data[133].label = C;
  data[134].feature[0] = 6.7;
  data[134].feature[1] = 3.3;
  data[134].feature[2] = 5.7;
  data[134].feature[3] = 2.5;
  data[134].label = C;
  return data;
}

struct Iris* create_test_data_set() {
  struct Iris* data = mem_malloc(data_size * sizeof(struct Iris));
  data[0].feature[0] = 4.8;
  data[0].feature[1] = 3.0;
  data[0].feature[2] = 1.4;
  data[0].feature[3] = 0.3;
  data[0].label = A;
  data[1].feature[0] = 5.1;
  data[1].feature[1] = 3.8;
  data[1].feature[2] = 1.6;
  data[1].feature[3] = 0.2;
  data[1].label = A;
  data[2].feature[0] = 4.6;
  data[2].feature[1] = 3.2;
  data[2].feature[2] = 1.4;
  data[2].feature[3] = 0.2;
  data[2].label = A;
  data[3].feature[0] = 5.3;
  data[3].feature[1] = 3.7;
  data[3].feature[2] = 1.5;
  data[3].feature[3] = 0.2;
  data[3].label = A;
  data[4].feature[0] = 5.0;
  data[4].feature[1] = 3.3;
  data[4].feature[2] = 1.4;
  data[4].feature[3] = 0.2;
  data[4].label = A;
  data[5].feature[0] = 5.7;
  data[5].feature[1] = 3.0;
  data[5].feature[2] = 4.2;
  data[5].feature[3] = 1.2;
  data[5].label = B;
  data[6].feature[0] = 5.7;
  data[6].feature[1] = 2.9;
  data[6].feature[2] = 4.2;
  data[6].feature[3] = 1.3;
  data[6].label = B;
  data[7].feature[0] = 6.2;
  data[7].feature[1] = 2.9;
  data[7].feature[2] = 4.3;
  data[7].feature[3] = 1.3;
  data[7].label = B;
  data[8].feature[0] = 5.1;
  data[8].feature[1] = 2.5;
  data[8].feature[2] = 3.0;
  data[8].feature[3] = 1.1;
  data[8].label = B;
  data[9].feature[0] = 5.7;
  data[9].feature[1] = 2.8;
  data[9].feature[2] = 4.1;
  data[9].feature[3] = 1.3;
  data[9].label = B;
  data[10].feature[0] = 6.7;
  data[10].feature[1] = 3.0;
  data[10].feature[2] = 5.2;
  data[10].feature[3] = 2.3;
  data[10].label = C;
  data[11].feature[0] = 6.3;
  data[11].feature[1] = 2.5;
  data[11].feature[2] = 5.0;
  data[11].feature[3] = 1.9;
  data[11].label = C;
  data[12].feature[0] = 6.5;
  data[12].feature[1] = 3.0;
  data[12].feature[2] = 5.2;
  data[12].feature[3] = 2.0;
  data[12].label = C;
  data[13].feature[0] = 6.2;
  data[13].feature[1] = 3.4;
  data[13].feature[2] = 5.4;
  data[13].feature[3] = 2.3;
  data[13].label = C;
  data[14].feature[0] = 5.9;
  data[14].feature[1] = 3.0;
  data[14].feature[2] = 5.1;
  data[14].feature[3] = 1.8;
  data[14].label = C;
  return data;
}