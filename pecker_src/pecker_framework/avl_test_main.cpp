#include <Windows.h>
#include "data/PeckerArray.h"
#include "data/pecker_avl_tree_algorithm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

USING_PECKER_SDK

struct stringcmp_
{
	inline int operator () (const std::string & str1,const std::string & str2) const
	{
		return str1.compare(str2);
	}
};

typedef enum 
{
	CMD_NONE = 0,
	CMD_ADD,
	CMD_SEARCH,
	CMD_DEL,
	CMD_CLR,
	CMD_TRAINORDER,
	CMD_TRACOVORDDER,
	//CMD_SHOWALL,
	CMD_COUNT,
}CMD_INOUT;

void avl_alg_func_main()
{
	std::ifstream myfile;
	myfile.close();
	myfile.open("inputcmdanddata.txt");

	nINDEX indextest = 0;
	int i =0;
	AVL_node_map<std::string,int>* pavl_root_node = null;
	AVL_node_map<std::string,int>* pavl_tmp_node = null;
	CMD_INOUT cmdType = CMD_NONE;
	Bool bVisiable = true;
	int index = 0;
	stringcmp_ cmp_m;
	HResult hres;
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;
		if ("[printfn]"==strin)
		{
			std::cout << "===============node buff=========== "<< std::endl;
			std::cout << "=================================== "<< std::endl;
			
			continue;
		}
		if ("[printfsn]"==strin)
		{
			std::cout << "===============save node buff=========== "<< std::endl;
			std::cout << "=================================== "<< std::endl;
		  
			continue;
		}
		if ("[show]"==strin)
		{
			std::cout << "===============all tree============= "<< std::endl;
			std::cout << "=================================== "<< std::endl;
			
			continue;
		}
		if ("[none]"==strin)
		{
			cmdType = CMD_NONE;
			continue;
		}
		if ("[add]"==strin)
		{
			cmdType = CMD_ADD;
			std::cout << "===============add============= "<< std::endl;
			continue;
		}
		else if ("[del]"==strin)
		{
			cmdType = CMD_DEL;
			std::cout << "===============del============= "<< std::endl;
			continue;
		}
		else if("[search]"==strin)
		{
			cmdType = CMD_SEARCH;
			std::cout << "===============search============= "<< std::endl;
			continue;
		}
		else if ("[clr]"==strin)
		{
			cmdType = CMD_CLR;
			std::cout << "===============clr============= "<< std::endl;
			//continue;
		}
		else if ("[incorder]"==strin)
		{
			cmdType = CMD_TRAINORDER;
			std::cout << "===============incorder============= "<< std::endl;
			continue;
		}
		else if ("[decorder]"==strin)
		{
			cmdType = CMD_TRACOVORDDER;
			std::cout << "===============decorder============= "<< std::endl;
			continue;
		}
		else if ("[Visiable]"==strin)
		{
			bVisiable = true;
			continue;
		}
		else if ("[Hide]"==strin)
		{
			bVisiable = false;
			continue;
		}

		switch (cmdType)
		{
		case CMD_ADD:
			{
				AVL_node_map<std::string,int>* pavl_node = new AVL_node_map<std::string,int>();
				pavl_node->key = strin;
				pavl_node->value = index++;
				//pavl_node->_p_char = strin.data();
				//pavl_node->_t_char = *strin.data();
				#ifdef AVL_DEBUG_CODE
				pavl_node->teststr = strin;
                #endif
				pavl_tmp_node = avl_tree_add< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,pavl_node, cmp_m,hres);
				if (null != pavl_tmp_node)
				{
					std::cout <<"add node=" <<pavl_tmp_node->key << " res=" << hres << " height=" << pavl_tmp_node->_M_height << std::endl;
				}
				else
				{
					std::cout << "add node null" << std::endl;
				}
			}
			break;
		case CMD_SEARCH:
			 pavl_tmp_node = avl_tree_find_referance< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,strin, cmp_m);
			 if (null == pavl_tmp_node)
			 {
				 std::cout << "find null" << std::endl;
			 }
			 else
			 {
				 std::cout <<"find node=" <<pavl_tmp_node->key << " height=" << pavl_tmp_node->_M_height ;
				 std::cout << " left node =" ;
				 if (pavl_tmp_node->_M_left)
				 {
					 std::cout << (long)(pavl_tmp_node->_M_left);
					 // std::cout << pavl_tmp_node->_M_left->_t_char ;
                     #ifdef AVL_DEBUG_CODE
					 std::cout << pavl_tmp_node->_M_left->teststr;
                     #endif
				 }
				 else
					 std::cout << "null";

				 std::cout << " right node =" ;
				 if (pavl_tmp_node->_M_right)
				 {
					 std::cout << (long)(pavl_tmp_node->_M_right);
					 //std::cout << pavl_tmp_node->_M_right->_t_char;
					 #ifdef AVL_DEBUG_CODE
					 std::cout << pavl_tmp_node->_M_left->teststr;
                     #endif
				 }
				 else
					 std::cout << "null";

				   std::cout <<  std::endl;
			 }
			break;
		case CMD_DEL:
			pavl_tmp_node = avl_tree_remove< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,strin, cmp_m,hres);
			if (null != pavl_tmp_node)
			{
				std::cout <<"del node=" <<pavl_tmp_node->key << " res=" << hres << std::endl;
				delete pavl_tmp_node;
				pavl_tmp_node = null;
			}
			else
			{
				std::cout << "del node null" << std::endl;
			}
			break;
		case CMD_CLR:
			
			break;
		case CMD_TRAINORDER:
			std::cout << "===============trav inorder============= "<< std::endl;
			break;
		case CMD_TRACOVORDDER:
			std::cout << "=============trav decorder =============="<< std::endl;
			break;
		default:
			break;
		}
	}

	int ibreak;
	std::cin >> ibreak;
}


int avl_cmp_stress_main()
{
	CPeckerArray< std::string > ArrList(100000,256);
	ArrList.Resize(0);
	std::vector< std::string > vecList;
	nINDEX indextest = 0;

	LARGE_INTEGER litmp; 
	LONGLONG QPartStartTick,QPartStopTick;
	double dfMinus, dfFreq, dfAddTime,dfSearchTime,dfDelTime; 
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;   // 获得计数器的时钟频率

	std::ifstream myfile;

	myfile.close();
	myfile.open("inputaddsearch.txt");

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;               // 获得初始值
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfSearchTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒

	std::cout << "read file time = " << dfSearchTime << std::endl;

	myfile.close();
	myfile.open("inputaddsearch.txt");

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	while(1)
	{
		if (myfile.eof())
			break;

		std::string strin;
		myfile >> strin;

		//vecList.push_back(strin);
		ArrList.AddEnd(strin);
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "load file to mem "<< dfAddTime << std::endl;

	//std::cout << sizeof(std::string) << std::endl;
	//std::cout << sizeof (AVL_node_map<std::string,int>) << std::endl;


	AVL_node_map<std::string,int>* pavl_root_node = null;
	AVL_node_map<std::string,int>* pavl_tmp_node = null;
	//PeckerCompareHandleEquals<std::string> cmp_m;
	stringcmp_ cmp_m;

	
	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	HResult hres = 0;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
	//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		
		AVL_node_map<std::string,int>* pavl_node = new AVL_node_map<std::string,int>();
		//pavl_node->key = vecList[idx];
		pavl_node->key = *ArrList.GetAtRef(idx);
		pavl_node->value = idx;
		#ifdef AVL_DEBUG_CODE
		pavl_node->teststr = pavl_node->key;
        #endif
		//pavl_node->_p_char = (pavl_node->key.data());
		//avl_tree_add< std::string, AVL_node_map<std::string,int>, PeckerCompareHandleEquals<std::string> > (pavl_root_node,pavl_node, cmp_m,hres);
		avl_tree_add< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,pavl_node, cmp_m,hres);
		//std::cout << idx << std::endl;
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl add "<< dfAddTime << std::endl;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
	//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		//if (null == avl_tree_find< std::string, AVL_node_map<std::string,int>, PeckerCompareHandleEquals<std::string> > (pavl_root_node,vecList[idx], cmp_m))
		//if (null == avl_tree_find< std::string, AVL_node_map<std::string,int>, PeckerCompareHandleEquals<std::string> > (pavl_root_node,*ArrList.GetAtRef(idx), cmp_m))

		const AVL_node_map<std::string,int>* pfind = avl_tree_find< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,*ArrList.GetAtRef(idx), cmp_m);
		if (null == pfind)
		{
			std::cout << "find add null "<< std::endl;
		}
		else
		{
			int height = calculate_avl_node_height(pfind);
			int bval = calculate_avl_node_balance_val(pfind);
			if (height != pfind->_M_height)
			{
				std::cout << "find height diff "<< std::endl;
			}
			if (bval >= 2 || bval <= -2)
			{
				std::cout << "find bval err "<< std::endl;
			}
		}

	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl find "<< dfAddTime << std::endl;

	std::string finstr = "approach";//"ancestor";
	//std::string finstrarr[] = {"approach","assist","attend","author","batter","battle","beg","bite","aboard",
	//	"bleed","blast","boil","breathe","abroad","breadth","kindle","capable","cabinet","car",
	//	"webcast","cell","cent","century","central","certain","certify","choose","choice","chop",
	//	"chip","Christ","city","cleanly","enclose","closely","clothes","cock","combine",
	//	"come","welcome","commune","communication","company","complementary",
	//	"confidence","connection","copper","cop","costly","count1","accounting","count2",
	//	"county","course","concur","cover","coward","crack","creator","cripple","crossing",
	//	"crucify","crucial","custom","accustomed","customer","shortcut","danger",
	//	"daring","dependence","dialog(ue)","apology","dictate","diction","deadly","confer",
	//	"directly","director","erect","disappoint","distinguishable","diploma","diplomatic",
	//	"drama","draft","dress","dry","due","southern","collect","a./ad.","collection",
	//	"electric","electron","element","emperor","empress","engineer","entrance",
	//	"entry","entertain","equal","equip","equipment","essential","overestimate","underestimate",
	//	"event","excellent","exception","exhibit","prohibition","expanse","aspect",
	//	"perspective","prospective","spectacular","expert","experimental","experimentation",
	//	"explain","explode","explosive","applaud","applause","facial","superficial",
	//	"factor","affect","infectious","manufacture","manufacturer","fantastic","welfare",
	//	"fast","fate","favo(u)rable","fear","feel","figure","confirm","confirmation","infirm",
	//	"reflection,-exion","influential","flower","flour","flock","feed",
	//	"bid","enforce1","enforce2","fort","conform","formal","formation","formula","performance",
	//	"information","inform","fortune","unfortunate","unfortunately","fund",
	//	"refreshment","confront","full","fill","game","kindergarten","gasoline/-ene","genuine",
	//	"generalization","forget","get-together","glisten","glimpse","foregoing",
	//	"better","grateful","congratulate","congratulation","postgraduate","undergraduate",
	//	"kilogram(me)","program(me)","granddaughter","grip","evergreen","greeting","underground",
	//	"grow","grown-up","growth","guard","regard","guide","guidance","guilt",
	//	"guilty","habit","habitual","cohabit","inhabit","inhabitant","behalf","quarter",
	//	"headquarters","beforehand","handkerchief","handwriting","left-handed","right-handed",
	//	"second-hand","handful","handle","handsome","manual","comprehension","comprehensive",
	//	"commend","recommendation","harden","hardship","hardly","harmful",
	//	"hateful","hatred","behave"};
	//std::string finstrarr[] = {
	//	"beg" ,
	//	"kindle" ,
	//	"car" ,
	//	"century" ,
	//	"central" ,
	//	"certain" ,
	//	"certify" ,
	//	"cleanly" ,
	//	"closely" ,
	//	"clothes" ,
	//	"combine" ,
	//	"copper" ,
	//	"cop" ,
	//	"costly" ,
	//	"count1" ,
	//	"count2" ,
	//	"county" ,
	//	"course" ,
	//	"concur" ,
	//	"coward" ,
	//	"condemn" ,
	//	"dean" ,
	//	"deep" ,
	//	"deny" ,
	//	"dictate" ,
	//	"diction" ,
	//	"confer" ,
	//	"erect" ,
	//	"dirt" ,
	//	"distinguishable" ,
	//	"deed" ,
	//	"dog-eared" ,
	//	"door" ,
	//	"diploma" ,
	//	"dramatics" ,
	//	"drag" ,
	//	"economics" ,
	//	"det." ,
	//	"collect" ,
	//	"entry" ,
	//	"equal" ,
	//	"equip" ,
	//	"event" ,
	//	"experimentation" ,
	//	"fast" ,
	//	"fate" ,
	//	"fear" ,
	//	"feel" ,
	//	"confirm" ,
	//	"infirm" ,
	//	"reflection,-exion" ,
	//	"feed" ,
	//	"bid" ,
	//	"reinforce" ,
	//	"conform" ,
	//	"transform" ,
	//	"inform" ,
	//	"fill" ,
	//	"telegraph" ,
	//	"easygoing" ,
	//	"regarding" ,
	//	"habit" ,
	//	"cohabit" ,
	//	"hairy" ,
	//	"halve" ,
	//	"shorthand" ,
	//	"handy" ,
	//	"recommendation" ,
	//	"hinge" 
	//};
	//int lenstr = 66;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;

	int delnullcount = 0;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
		//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		//if (idx == 97)
		//{
		//	idx = idx;
		//}
		//if (idx == 190)
		//{
		//	idx = idx;
		//}
		//for(int i=0;i<lenstr;++i)
		//{
		//	AVL_node_map<std::string,int>* pfind = avl_tree_find< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,finstrarr[i], cmp_m);
		//	if (null == pfind)
		//	{
		//		pfind = pfind;
		//	}
		//}

		pavl_tmp_node = avl_tree_remove< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,*ArrList.GetAtRef(idx), cmp_m,hres);

		//AVL_node_map<std::string,int>* pfind = avl_tree_find< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,finstr, cmp_m);
		//if (null == pfind)
		//{
		//	pfind = pfind;
		//}
		//for(int i=0;i<lenstr;++i)
		//{
		//	AVL_node_map<std::string,int>* pfind = avl_tree_find< std::string,stringcmp_, AVL_node_map<std::string,int> > (pavl_root_node,finstrarr[i], cmp_m);
		//	if (null == pfind)
		//	{
		//		pfind = pfind;
		//	}
		//}

		if (null != pavl_tmp_node)
		{
			//std::cout <<"del node=" <<pavl_tmp_node->key << " res=" << hres << std::endl;
			delete pavl_tmp_node;
			pavl_tmp_node = null;
		}
		else
		{
			delnullcount++;
			std::cout << "\""<<*ArrList.GetAtRef(idx) <<"\" , "<<std::endl;
			//std::cout << "del node null " << delnullcount <<  " str = "<< *ArrList.GetAtRef(idx) <<std::endl;
		}

	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "avl erase "<< dfAddTime << std::endl;
	

	std::map<std::string , int >mapstring;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
		//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		mapstring.insert(std::map<std::string , int >::value_type( *ArrList.GetAtRef(idx),idx));
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map add "<< dfAddTime << std::endl;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
		//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		mapstring.find(*ArrList.GetAt(idx));
	}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map find "<< dfAddTime << std::endl;

	QueryPerformanceCounter(&litmp);
	QPartStartTick = litmp.QuadPart;
	for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
		//for (nINDEX idx=0;idx<vecList.size();++idx)
	{
		mapstring.erase(*ArrList.GetAt(idx));
	}
	//{
	//	std::map< std::string, int > releasemap;
	//	releasemap.swap(mapstring);
	//}
	QueryPerformanceCounter(&litmp);
	QPartStopTick = litmp.QuadPart;   //获得中止值
	dfMinus = (double)(QPartStopTick-QPartStartTick);
	dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	std::cout << "stl map erase "<< dfAddTime << std::endl;

	//QueryPerformanceCounter(&litmp);
	//QPartStartTick = litmp.QuadPart;
	////for (nINDEX idx=0;idx<ArrList.GetCollectionSize();++idx)
	//for (nINDEX idx=0;idx<vecList.size();++idx)
	//{
	//	HResult hres = 0;
	//	AVL_node_map<std::string,int>* pavl_del_node = avl_tree_erase< std::string, AVL_node_map<std::string,int>, PeckerCompareHandleEquals<std::string> >(pavl_root_node,vecList[idx],cmp_m,hres);
	//	if (null ==  pavl_del_node)
	//	//	avl_tree_find< std::string, AVL_node_map<std::string,int>, PeckerCompareHandleEquals<std::string> > (pavl_root_node,vecList[idx], cmp_m))// (pavl_root_node,*ArrList.GetAtRef(idx), cmp_m))
	//	{
	//		std::cout << "erase  null "<< std::endl;
	//	}
	//	else
	//	{
	//		delete pavl_del_node;
	//		pavl_del_node = null;
	//	}
	//	

	//}
	//QueryPerformanceCounter(&litmp);
	//QPartStopTick = litmp.QuadPart;   //获得中止值
	//dfMinus = (double)(QPartStopTick-QPartStartTick);
	//dfAddTime = dfMinus / dfFreq;    // 获得对应的时间值，单位为秒
	//std::cout << "erase "<< dfAddTime << std::endl;


	//int ibreak = 0;
	//std::cin >> ibreak;

	return 0;
}