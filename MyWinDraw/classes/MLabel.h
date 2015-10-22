#ifndef __MLABEL_H__
#define __MLABEL_H__
#include "MNode.h"
#include <string>
#include <stdio.h>
#include "./MImpl/MLabelImpl.h"
class MLabel : public MNode
{
public:
	MLabel();
	~MLabel();
	CreateFunc(MLabel);
	static MLabel* create(const char* _str, uint _size, MColor _color = MColor(255, 255, 255));
	void initLabel(const char* _str, uint _size, MColor _color = MColor(255, 255, 255));
	void setString(const char* _str);
	void setColor(const MColor& _color);
	virtual void setPoint(const MPoint& _p);
private:	
	virtual void draw();
private:
	MLabelImpl* m_labelImpl;
	std::string* m_str;
	uint m_fontSize;
	MColor m_color;
};
#endif