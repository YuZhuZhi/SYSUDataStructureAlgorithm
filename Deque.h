#pragma once
#include <vector>

//�����ʹ��std::vectorģ����С�
//����ֱ��Ĭ��Ϊ������˫����ӳ��ӵ�ѭ�����С�

template <typename _T>
class Deque
{
public:
	Deque() = delete; //�������ڲ���������������¹������
	Deque(const Deque<_T>& deque) = default;
	Deque(Deque<_T>&& deque) = default;
	Deque(const int size)
	{ //Ĭ��Ϊ˫��ѭ������
		_size = size;
		_deque.resize(size);
	}
	Deque(const bool limpush, const bool limpop, const int size)
	{ //ͨ��limpush, limpop���������Ƿ�˫���������
		_size = size;
		_limpush = limpush;
		_limpop = limpop;
		_deque.resize(size);
	}
	~Deque() = default;
	int Size() const
	{ //�����������Ԫ�ظ���
		if (_flag) return 0; //�������Ϊ��
		else {
			if (_front < _rear) return (_rear - _front);
			else return (_size - _front + _rear);
		}
	}
	bool Full() const
	{ //�ж϶����Ƿ�����
		if (_flag) return false;
		else if (_size == Size()) return true; //�������Ԫ�ظ������ڶ�������
		else return false;
	}
	bool Empty() const
	{ //�ж϶����Ƿ�Ϊ��
		if (_flag) return true;
		else return false;
	}
	bool PushBack(const _T& data)
	{ //�����Ƿ�����˫����ӣ��������Ӻ����
		if (Full()) return false; //����������������ʧ��
		else {
			_rear = (_rear + 1) % _size; //��β�����һλ
			_deque[_rear] = data;
			_flag = false; //���в��ǿն���
			return true; //��ӳɹ�
		}
	}
	bool PushFront(const _T& data)
	{ //����˫�����ʱ����ֹ��ǰ���
		if (_limpush) return false;
		else {
			if (Full()) return false; //����������������ʧ��
			else {
				_deque[_front] = data;
				_front = (_front == 0) ? (_size - 1) : _front - 1; //��ͷ��ǰ��һλ
				_flag = false; //���в��ǿն���
				return true; //��ӳɹ�
			}
		}
	}
	bool PopBack(_T& returner)
	{ //����˫�˳���ʱ����ֹ�Ӻ����
		if (_limpop) return false;
		else {
			returner = _deque[_rear];
			_rear = (_rear == 0) ? (_size - 1) : _rear - 1; //��β��ǰ��һλ
			if (_front == _rear) _flag = true; //�����β�Ӻ����϶�ͷ����ô����Ϊ��
			return true; //���ӳɹ�
		}
	}
	bool PopFront(_T& returner)
	{ //�����Ƿ�����˫�˳��ӣ���������ǰ����
		if (Empty()) return false; //�������Ϊ�գ�����ʧ��
		else {
			_front = (_front + 1) % _size; //��ͷ�����һλ
			returner = _deque[_front];
			if (_front == _rear) _flag = true; //�����ͷ��ǰ׷�϶�β����ô����Ϊ��
			return true; //���ӳɹ�
		}
	}
	_T Back() const
	{ //������ȡ��β����
		if (Empty()) return ((_T)NULL);
		else return (_deque[_rear]);
	}
	_T Front() const
	{ //������ȡ��ͷ����
		if (Empty()) return ((_T)NULL);
		else {
			if (_front != _size - 1) return (_deque[_front + 1]);
			else return (_deque[0]);
		}
	}

private:
	std::vector<_T> _deque; //�ײ����ݽṹ
	int _size = 0; //��������
	int _front = 0; //��ʾ��ͷ�±꣬��Ԫ���ڶ�ͷ��һ��λ
	int _rear = 0; //��ʾ��β�±�
	bool _flag = true; //_flag��ʾ�����Ƿ�Ϊ�ա�����Ϊ�ա�
	bool _limpush = false; //�Ƿ�����˫����ӡ�����Ϊ���ơ�
	bool _limpop = false; //�Ƿ�����˫�˳��ӡ�����Ϊ���ơ�

};