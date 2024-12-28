#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <stdexcept>
#include <utility>

template<typename Type>
class CustomList {
private:
	struct Element {
		Type data;
		Element* next = nullptr;
	};

	Element* firstElement;
	Element* lastElement;
	size_t elementCount;

	Element* fetchElement(size_t index) const;

public:
	CustomList();
	CustomList(const CustomList& source);
	CustomList(CustomList&& source) noexcept;
	~CustomList();

	size_t length() const noexcept;
	bool empty() const noexcept;

	void addToEnd(const Type& data);
	void addToStart(const Type& data);
	void eraseAt(size_t index);
	void reset();

	Type& getItem(size_t index);
	const Type& getItem(size_t index) const;

	bool operator==(const CustomList& source) const noexcept;
	bool operator!=(const CustomList& source) const noexcept;

	CustomList& operator=(const CustomList& source);
	CustomList& operator=(CustomList&& source) noexcept;

	class Iter {
	private:
		Element* currentElem;
	public:
		explicit Iter(Element* element) : currentElem(element) {}
		Iter& operator++() { currentElem = currentElem->next; return *this; }
		bool operator==(const Iter& other) const { return currentElem == other.currentElem; }
		bool operator!=(const Iter& other) const { return currentElem != other.currentElem; }
		Type& operator*() { return currentElem->data; }
	};

	Iter begin() const { return Iter(firstElement); }
	Iter end() const { return Iter(nullptr); }
};

template<typename Type>
CustomList<Type>::CustomList() : elementCount(0), firstElement(nullptr), lastElement(nullptr) {}

template<typename Type>
CustomList<Type>::CustomList(const CustomList& source) : elementCount(0), firstElement(nullptr), lastElement(nullptr) {
	for (Element* node = source.firstElement; node; node = node->next)
		addToEnd(node->data);
}

template<typename Type>
CustomList<Type>::CustomList(CustomList&& source) noexcept
	: firstElement(source.firstElement), lastElement(source.lastElement), elementCount(source.elementCount) {
	source.firstElement = source.lastElement = nullptr;
	source.elementCount = 0;
}

template<typename Type>
CustomList<Type>::~CustomList() { reset(); }

template<typename Type>
typename CustomList<Type>::Element* CustomList<Type>::fetchElement(size_t index) const {
	if (index >= elementCount) throw std::out_of_range("Index out of range");
	Element* temp = firstElement;
	for (size_t i = 0; i < index; ++i)
		temp = temp->next;
	return temp;
}

template<typename Type>
size_t CustomList<Type>::length() const noexcept { return elementCount; }

template<typename Type>
bool CustomList<Type>::empty() const noexcept { return elementCount == 0; }

template<typename Type>
void CustomList<Type>::addToEnd(const Type& data) {
	Element* newNode = new Element{ data };
	if (lastElement)
		lastElement->next = newNode;
	else
		firstElement = newNode;

	lastElement = newNode;
	++elementCount;
}

template<typename Type>
void CustomList<Type>::addToStart(const Type& data) {
	Element* newNode = new Element{ data, firstElement };
	firstElement = newNode;
	if (!lastElement)
		lastElement = newNode;
	++elementCount;
}

template<typename Type>
void CustomList<Type>::eraseAt(size_t index) {
	if (index >= elementCount) throw std::out_of_range("Index out of range");

	Element* toRemove = nullptr;
	if (index == 0) {
		toRemove = firstElement;
		firstElement = firstElement->next;
		if (!firstElement) lastElement = nullptr;
	}
	else {
		Element* prev = fetchElement(index - 1);
		toRemove = prev->next;
		prev->next = toRemove->next;
		if (index == elementCount - 1) lastElement = prev;
	}

	delete toRemove;
	--elementCount;
}

template<typename Type>
void CustomList<Type>::reset() {
	while (firstElement) {
		Element* temp = firstElement;
		firstElement = firstElement->next;
		delete temp;
	}
	lastElement = nullptr;
	elementCount = 0;
}

template<typename Type>
Type& CustomList<Type>::getItem(size_t index) { return fetchElement(index)->data; }

template<typename Type>
const Type& CustomList<Type>::getItem(size_t index) const { return fetchElement(index)->data; }

template<typename Type>
bool CustomList<Type>::operator==(const CustomList& source) const noexcept {
	if (elementCount != source.elementCount) return false;
	Element* current1 = firstElement;
	Element* current2 = source.firstElement;
	while (current1) {
		if (current1->data != current2->data) return false;
		current1 = current1->next;
		current2 = current2->next;
	}
	return true;
}

template<typename Type>
bool CustomList<Type>::operator!=(const CustomList& source) const noexcept { return !(*this == source); }

template<typename Type>
CustomList<Type>& CustomList<Type>::operator=(const CustomList& source) {
	if (this == &source) return *this;
	reset();
	for (Element* node = source.firstElement; node; node = node->next)
		addToEnd(node->data);
	return *this;
}

template<typename Type>
CustomList<Type>& CustomList<Type>::operator=(CustomList&& source) noexcept {
	if (this == &source) return *this;
	reset();
	firstElement = source.firstElement;
	lastElement = source.lastElement;
	elementCount = source.elementCount;
	source.firstElement = source.lastElement = nullptr;
	source.elementCount = 0;
	return *this;
}

#endif
