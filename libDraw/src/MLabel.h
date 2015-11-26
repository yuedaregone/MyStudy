#ifndef __MLABEL_H__
#define __MLABEL_H__
#include "MNode.h"
#include <string>
#include <stdio.h>
#include "./MImpl/MLabelImpl.h"
class CC_DLL MLabel : public MNode
{
public:
	MLabel();
	~MLabel();
	CreateFunc(MLabel);
	static MLabel* create(const char* _str, uint _size, MColor _color = MColor(255, 255, 255));
	void initLabel(const char* _str, uint _size, MColor _color = MColor(255, 255, 255));
	void setString(const char* _str);
	void setColor(const MColor& _color);	
	void setFontSize(uint _size);
private:	
	virtual void draw();
private:
	MLabelImpl* m_labelImpl;
	std::string* m_str;
	uint m_fontSize;
	MColor m_color;
};
#endif