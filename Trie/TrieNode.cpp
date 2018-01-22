/*============================================================================
 * Filename: TrieNode.cpp
 * Author: Zongyue Qin
 * Mail: qinzongyue@pku.edu.cn
 * Last modified:	2018-01-15
 * Description:
 * Implementing functions in TrieNode.h
 =============================================================================*/
#include "TrieNode.h"
#include <cstdio>
#include <iostream>

using namespace std;

TrieNode::TrieNode()
{
	lchd = rbro = NULL;
	str = "";
	count = 0;
	ID = -1;
}

TrieNode::TrieNode(const string &_str)
{
	lchd = rbro = NULL;
	str = _str;
	count = 0;
	ID = -1;
}

/* Addstring
 * insert string into one of its children
 */
void
TrieNode::addString(string& _str, int _ID)
{
	count++;

	if (_str.length() == 0)		// the whole string is inserted
	{
		this->ID = _ID;
		return;
	}

	string strPiece = split(_str);
	TrieNode* child = this->lchd;

	while (child != NULL)
	{
		if (strPiece == child->str)
		{
			child->addString(_str, _ID);
			return;
		}
		child = child->rbro;
	}

	/* no child matching strPiece */
	TrieNode *p = new TrieNode(strPiece);

	child = this->lchd;
	p->rbro = child;
	this->lchd = p;
	p->addString(_str, _ID);
	
	return;	
}

/* compress:
 * compress string and print into output files */
string
TrieNode::compress(string& _str, const int& lowbound)
{
	string strPiece = split(_str);
	TrieNode *child = this->lchd;

	while (child != NULL)
	{
		if (strPiece == child->str)
		{
			if (child->count > lowbound)
			{
				return child->compress(_str, lowbound);
			}
			else break;
		}
		child = child->rbro;
	}

	/* Compressing ends here */

	/* recover _str */
	if (_str != "")
	strPiece = strPiece + _str;
	//strPiece = strPiece + "/" + _str;

	if (this->ID < 0)
	{
		cerr << "TrieNode::compress error. ID = " << ID << " str = " << 
		strPiece << endl;
		cerr << this->getString() << endl;
		cerr << this->getCount() << endl;
		return "";
	}

	char buf[10];
	sprintf(buf, "%d", this->ID);
	
	string retval = buf;
	retval += ("/" + strPiece);
/*
	if (strPiece.length() > 0)	// still has strings uncompressed
	{
		if (this->str != "")
			retval +=  ("//" + strPiece);
		else
			retval += "/" + strPiece;

	}
	else
		retval += "/";
*/
	return retval;
}

/* split:
 * return substring of _str before the first '/', and delete the substring
 * from _str
 */
string
TrieNode::split(string& _str)
{
	int len = _str.length();
	int i = 0;
	
	while (i < len)
	{
		if (_str[i] == '/' || _str[i] == '.')
		{
			// ignore first char because it's '.' or '/'
			// and there might be "//"
			if (i > 0 && _str[i - 1] != '/') break;
		}
		i++;
	}

	string ret = _str.substr(0, i);
	if (i < len)
		_str = _str.substr(i, len - i);
	else
 		_str = "";

	return ret;
}

void
TrieNode::addCount()
{
	count++;
}

void
TrieNode::setLchd(const TrieNode *_lchd)
{
	lchd = (TrieNode *) _lchd;
}

void
TrieNode::setRbro(const TrieNode *_rbro)
{
	rbro = (TrieNode *) _rbro;
}

void
TrieNode::setString(const string &_str)
{
	str = _str;
}

int
TrieNode::getCount()
{
	return count;
}

TrieNode*
TrieNode::getLchd()
{
	return lchd;
}

TrieNode*
TrieNode::getRbro()
{
	return rbro;
}

string
TrieNode::getString()
{
	return str;
}

