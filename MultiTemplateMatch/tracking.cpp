#include "tracking.h"
#include "calSimilarity.h"
void tracking(Mat &src, Object& obj)
{
	//-------------------------------------------ģ��ƥ��-------------------------------//
	double maxSimilarity = 0;
	double minSimilarity = 10000;
	int candidateShiftIndex = 0;
	int maxSimilarityTemplateIndex = 0;
	Mat tempCandidateTargetMat = Mat(obj.templateHeight, obj.templateWidth, CV_8UC1);
	vector<vector <double> > allTemplateSimilarity;

	//-------------------------------------------����������ʼ��-------------------------//
	calShiftSimilarMat(obj.ShiftSimilarMat, obj.similarMat);
	//namedWindow("test");
	char outfilename[200] = {0};
	//-------------------------------------------��������-------------------------------//
	for(int i = 0; i < SHIFT_NUM; i ++)
	{
		getFeature(src, tempCandidateTargetMat, obj.ShiftSimilarMat[i]);
		//imshow("test", tempCandidateTargetMat);
		//sprintf(outfilename,"C:\\Users\\wulala1119\\Documents\\visual studio 2012\\Projects\\MultiTemplateMatch\\template\\template_%02d.jpg",i);
		//imwrite(outfilename, obj.templateFeature[i]);
		//cvWaitKey(0);
		for(int j = 0; j < obj.templateNum; j ++)
		{
			vector<double> similarityRes = calSimilarity(obj.templateFeature[j], tempCandidateTargetMat, NCC());
			if(similarityRes[0] > maxSimilarity)
			{
				maxSimilarity = similarityRes[0];
				candidateShiftIndex = i;
				maxSimilarityTemplateIndex = j;
			}
		}
	}

	//-------------------------------------------�����ѡĿ�������ƶ���Сģ��-----------//


	//-------------------------------------------�ڵ�����-------------------------------//


	//-------------------------------------------ģ�����-------------------------------//


	//-------------------------------------------���ٽ���-------------------------------//


	//-------------------------------------------����λ��-------------------------------//
	obj.sx = obj.ShiftSimilarMat[candidateShiftIndex][0];
	obj.tx = obj.ShiftSimilarMat[candidateShiftIndex][1];
	obj.sy = obj.ShiftSimilarMat[candidateShiftIndex][2];
	obj.ty = obj.ShiftSimilarMat[candidateShiftIndex][3];
	obj.similarityMat2Position();

}
void calShiftSimilarMat(float ** ShiftSimilarMat, Mat& similarMat)
{
	float sx = similarMat.at<float>(0, 0);
	float tx = similarMat.at<float>(0, 2);
	float sy = similarMat.at<float>(1, 1);
	float ty = similarMat.at<float>(1, 2);
	int key = 0;
	for(int i = -1; i < 2; i ++)
	{		
		for(int j = -1; j < 2; j ++)
		{			
			for(int m = -1; m < 2; m ++)
			{
				for(int n = -1; n < 2; n ++)
				{
					ShiftSimilarMat[key][0] = sx + i * SX_SHIFT;
					ShiftSimilarMat[key][1] = tx + j * TX_SHIFT;
					ShiftSimilarMat[key][2] = sy + m * SY_SHIFT;
					ShiftSimilarMat[key][3] = ty + n * TY_SHIFT;
					key ++;
				}
			}
		}
	}
}