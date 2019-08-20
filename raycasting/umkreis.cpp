//erg=point with distance of x/y into direction mouse
void umkreis(float x, float y, float mouse_x, float mouse_y, float distance)
{
	float winkel = atan2(mouse_x - x, (mouse_y - y)*-1) * 180 / 3.1415926f;
	winkel = winkel < 0 ? winkel + 360 : winkel;
	float erg_x = x + sin(winkel * 3.1415926f / 180) * distance;
	float erg_y = y + cos(winkel * 3.1415926f / 180) * distance * -1;
	//cout<<winkel<<"-"<<erg_x<<"-"<<erg_y<<endl;
}