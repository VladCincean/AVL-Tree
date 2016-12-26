#pragma once

template <typename TE>
class SLList {
public:
	struct SLNode {
		SLNode* next;
		TE data;
	};

	class Iterator {
	private:
		SLNode* m_p;

	public:
		Iterator(SLNode* c = nullptr) : m_p(c) {}

		Iterator(const Iterator& it) {
			m_p = it.m_p;
		}

		Iterator& operator=(const Iterator& it) {
			m_p = it.m_p;
			return *this;
		}

		Iterator& operator++() {
			m_p = m_p->next;
			return *this;
		}

		//Iterator operator++(int);

		TE& operator*() const {
			return m_p->data;
		}

		TE* operator->() const {
			return &(operator*());
		}

		bool operator==(const Iterator& it) const {
			return m_p == it.m_p;
		}

		bool operator!=(const Iterator& it) const {
			return m_p != it.m_p;
		}
	};

private:
	SLNode* head;

public:
	SLList() : head(nullptr) {}

	SLList(const SLList& l) : head(nullptr) {
		for (Iterator it = l.begin(); it != l.end(); ++it)
			insertBack(*it);
	}

	~SLList() {
		while (head != nullptr) {
			SLNode* newHead = head->next;
			delete head;
			head = newHead;
		}
	}

	SLNode* getHead() {
		return head;
	}

	void insertFront(TE e) {
		SLNode* node = new SLNode;
		node->data = e;
		node->next = head;
		head = node;
	}

	void insertBack(TE e) {
		SLNode* node = head;
		while (node != nullptr && node->next != nullptr)
			node = node->next;
		if (node == nullptr)
			insertFront(e);
		else {
			SLNode* last = new SLNode;
			last->data = e;
			last->next = nullptr;
			node->next = last;
		}
	}

	void insertAfter(Iterator& it, TE e) {
		SLNode* node = new SLNode;
		node->data = e;
		node->next = it.m_p->next;
		it.m_p->next = node;
	}

	void eraseAfter(Iterator& it) {
		SLNode* node = it.m_p->next;
		if (it.m_p->next != nullptr)
			it.m_p->next = it.m_p->next->next;
		delete node;
	}

	void insertHere(Iterator& it, TE e) {
		SLNode* node = new SLNode;
		node->data = it.m_p->data;
		it.m_p->data = e;
		node->next = it.m_p->next;
		it.m_p->next = node;
	}

	void eraseHere(Iterator& it) {
		SLNode* node = it.m_p;
		while (node->next != nullptr) {
			node->data = node->next->data;
			if (node->next->next == nullptr) {
				delete node->next;
				node->next = nullptr;
				break;
			}
			node = node->next;
		}
	}

	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator();
	}
};
