// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <list>
#include <string>
#include <sstream>

#define  BOOST_DATE_TIME_NO_LIB

#define OUT
#define IN
#define SAFE_DELETE(p) {if((p)) { delete p; p = NULL; }}
#define RET(p) {if(p) return; }
#define RETV(p,ret) {if(p) return ret; }
