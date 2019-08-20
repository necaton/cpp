// -lcomdlg32
//alle bilder untereinander platzieren

#include "SFML/Graphics.hpp"
#include <iostream>
#include <windows.h>
#include <math.h>

using namespace sf;
using namespace std;

//variables
const string ordner = "pictures/";
const int offset = 5;
vector<string> dateien;
vector<Image> images;

struct pics {
	int height = 0;
	int width = 0;
	Image image;
} finalPicture;

vector <pics> pic;

int main()
{
	int width;
	cout<<"width: ";
	cin>>width;
	
	//pictureToVector
	WIN32_FIND_DATA wfd;
	HANDLE h;
	string search = ordner + "*";
	h = FindFirstFile(search.c_str(), &wfd);
	if(h != INVALID_HANDLE_VALUE) {
	  do {
		string filename = wfd.cFileName;
		if (filename == "." || filename == "..") continue;
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {
			//file
			dateien.push_back(ordner + filename);
		}
	  } while(FindNextFile(h, &wfd));
	  FindClose(h);
	}
	
	//pathToImage
	for (int i=0;i<dateien.size();i++)
	{
		Image image;
		image.loadFromFile(dateien.at(i));
		images.push_back(image);
	}
	
	//create row pics
	pics p;
	for (int i=0;i<images.size();i++)
	{
		if (i%width==0) {
			if (i!=0) pic.push_back(p);
			p.width = 0;
			p.height = 0;
		}
		p.width += images.at(i).getSize().x + offset;
		if (p.height < images.at(i).getSize().y) {
			p.height = images.at(i).getSize().y;
		}
	}
	pic.push_back(p);
	
	//create row pics raw
	for (int i=0;i<pic.size();i++)
	{
		pic.at(i).image.create(pic.at(i).width, pic.at(i).height);
		cout<<pic.at(i).width<<"-"<<pic.at(i).height<<endl;
	}
	
	//load images in row pics
	unsigned int rowx = 0;
	for (int i=0;i<images.size();i++)
	{
		if (i%width==0) {
			rowx = 0;
		}
		pic.at(i/width).image.copy(images.at(i), rowx, 0);
		rowx += images.at(i).getSize().x+offset;
	}
	
	//set finalPicture coords
	for (int i=0;i<pic.size();i++)
	{
		
		finalPicture.height += pic.at(i).image.getSize().y + offset;
		if (finalPicture.width < pic.at(i).image.getSize().x) {
			finalPicture.width = pic.at(i).image.getSize().x;
		}
	}
	
	//create finalPicture
	finalPicture.image.create(finalPicture.width, finalPicture.height);
	
	//load pictures into finalPicture
	unsigned int tempx, tempy = 0;
	for (int i=0;i<pic.size();i++)
	{
		tempx = (finalPicture.width - pic.at(i).image.getSize().x)/2;
		finalPicture.image.copy(pic.at(i).image, tempx, tempy);
		tempy += pic.at(i).image.getSize().y + offset;
	}
	
	//safe finalPicture
	finalPicture.image.saveToFile("Collage.jpg");
	
	cout<<"finished"<<endl;
	system("pause > nul");
	return 0;
}