#pragma once
#include <vector>

//这个类使用std::vector模拟队列。
//这里直接默认为不限制双端入队出队的循环队列。

template <typename _T>
class Deque
{
public:
	Deque() = delete; //不允许在不给定容量的情况下构造对象
	Deque(const Deque<_T>& deque) = default;
	Deque(Deque<_T>&& deque) = default;
	Deque(const int size)
	{ //默认为双端循环队列
		_size = size;
		_deque.resize(size);
	}
	Deque(const bool limpush, const bool limpop, const int size)
	{ //通过limpush, limpop参数限制是否双端输入输出
		_size = size;
		_limpush = limpush;
		_limpop = limpop;
		_deque.resize(size);
	}
	~Deque() = default;
	int Size() const
	{ //求队列中已有元素个数
		if (_flag) return 0; //如果队列为空
		else {
			if (_front < _rear) return (_rear - _front);
			else return (_size - _front + _rear);
		}
	}
	bool Full() const
	{ //判断队列是否已满
		if (_flag) return false;
		else if (_size == Size()) return true; //如果已有元素个数等于队列容量
		else return false;
	}
	bool Empty() const
	{ //判断队列是否为空
		if (_flag) return true;
		else return false;
	}
	bool PushBack(const _T& data)
	{ //无论是否限制双端入队，都保留从后入队
		if (Full()) return false; //如果队列已满，入队失败
		else {
			_rear = (_rear + 1) % _size; //队尾向后移一位
			_deque[_rear] = data;
			_flag = false; //队列不是空队列
			return true; //入队成功
		}
	}
	bool PushFront(const _T& data)
	{ //限制双端入队时，禁止从前入队
		if (_limpush) return false;
		else {
			if (Full()) return false; //如果队列已满，入队失败
			else {
				_deque[_front] = data;
				_front = (_front == 0) ? (_size - 1) : _front - 1; //队头向前移一位
				_flag = false; //队列不是空队列
				return true; //入队成功
			}
		}
	}
	bool PopBack(_T& returner)
	{ //限制双端出队时，禁止从后出队
		if (_limpop) return false;
		else {
			returner = _deque[_rear];
			_rear = (_rear == 0) ? (_size - 1) : _rear - 1; //队尾向前移一位
			if (_front == _rear) _flag = true; //如果队尾从后碰上队头，那么队列为空
			return true; //出队成功
		}
	}
	bool PopFront(_T& returner)
	{ //无论是否限制双端出队，都保留从前出队
		if (Empty()) return false; //如果队列为空，出队失败
		else {
			_front = (_front + 1) % _size; //队头向后移一位
			returner = _deque[_front];
			if (_front == _rear) _flag = true; //如果队头从前追上队尾，那么队列为空
			return true; //出队成功
		}
	}
	_T Back() const
	{ //仅作读取队尾数据
		if (Empty()) return ((_T)NULL);
		else return (_deque[_rear]);
	}
	_T Front() const
	{ //仅作读取队头数据
		if (Empty()) return ((_T)NULL);
		else {
			if (_front != _size - 1) return (_deque[_front + 1]);
			else return (_deque[0]);
		}
	}

private:
	std::vector<_T> _deque; //底层数据结构
	int _size = 0; //队列容量
	int _front = 0; //标示队头下标，首元素在队头后一个位
	int _rear = 0; //标示队尾下标
	bool _flag = true; //_flag标示队列是否为空。若真为空。
	bool _limpush = false; //是否限制双端入队。若真为限制。
	bool _limpop = false; //是否限制双端出队。若真为限制。

};