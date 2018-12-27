// template classes for single and double linked lists
// updated to work with latest ANSI C++ standards, on a GNU based system

/* each list type implements the following functions
legend: + functions part of base list class, inherited by both types of list
                - pure virtual functions, must be implemented by each list type

+	dword size()

+	void init()

+	T* getStart()
+	T* getCurrent()
+	T* getEnd()


+	T* goStart()
+	T* goEnd()
+	T* goDn()
-	T* goUp()

-	void addStart(T*)
-	void addEnd(T*)
-	void insBeforeCurrent(T*) // keeps current location
-	void insAfterCurrent(T*)  // keeps current location

-	T* removeStart()          // returns select node
-	T* removeCurrent()        //
-	T* removeEnd()            //

+	void addBeforeCurrent(T*) // makes current the new link
+	void addAfterCurrent(T*)  // makes current the new link1

// modifies list pointers
+	T* removeByInstance(T*)		// specify an item to remove from list (don't delete it)
+	T* remobeByIndex(unsigned)//

+	void removeAll() 					// destroys list nodes, not data nodes

+	void deleteStart()        //
+	void deleteCurrent()      //
+	void deleteEnd()          //
+	void deleteAll()					// destroys list nodes and data nodes

+	T* isInList(T*)						// returns ptr if is in list, null if not in list
+	T* betByInstance(T*)			// gets ptr by param, null if not in list (does not modify current pointer)
+	T* getByIndex(int)				// returns item in list by 1 based index

+	void set(xlist)   				//
+	void operator =	(xlist)		// destroy list & data nodes (if any), copy param to this list

+	void append(xlist)
+	void operator +=(xlist)		// append another list to end of this one

+	void operator <<(xlist)		// move contents of paramter list to this, null out param list
*/
#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "flags.h"
#include "Types.h"
// node structure for a single linked list
template <class T>
struct snode {
    T* data;
    void* next;
    snode() { data = NULL; next = NULL; }
};


// mode structure for a double linked list
template <class T>
struct dnode : public snode<T> {
    void* prev;
    dnode() : snode<T>() { prev = NULL; }
};

// common features of single & dowble linked lists
// this is a base class for slist and dlist
// implements duplicate functions common in single and double lists as
// virtual functions

template <class T>
class ListBase {
protected:
    flags<byte> mode;
    dword		linkCount;

    void*    	start;
    void*       current;
    void*   	end;

    void* 		oldStart;
    void*		oldCurrent;
    void*		oldEnd;

public:
    ListBase() {
        mode.Reset();
    }

    void	savePtrs() {
        oldStart = start;
        oldCurrent = current;
        oldEnd = end;
    }

    void	restPtrs() {
        start = oldStart;
        current = oldCurrent;
        end = oldEnd;
    }

    dword size() { return linkCount; }
    virtual void init() {
        start = NULL;
        current = NULL;
        end = NULL;
        linkCount = 0;
    }

    virtual T* getStart() { return (start) ? ((snode<T>*)start)->data : NULL; }
    virtual T* getCurrent() { return (current) ? ((snode<T>*)current)->data : NULL; }
    virtual T* getEnd() { return (end) ? ((snode<T>*)end)->data : NULL; }

        virtual T* getNext() {
                T* temp = getCurrent();
                goDn();
                return temp;
        }

    virtual T* goStart() { current = start; return (current) ? ((snode<T>*)current)->data : NULL; }
    virtual T* goEnd(){ current = end; return (current) ? ((snode<T>*)current)->data : NULL; }
    virtual T* goDn()	{if (current) current = ((snode<T>*)current)->next;	return (current) ? ((snode<T>*)current)->data : NULL; }

    virtual T* goUp() = 0;

    virtual void addStart(T*) = 0;
    virtual void addEnd(T*) = 0;
    virtual void insBeforeCurrent(T*) = 0;
    virtual void insAfterCurrent(T*) = 0;

    virtual T* removeStart() = 0;
    virtual T* removeCurrent() = 0;
    virtual T* removeEnd() = 0;

    virtual void addBeforeCurrent(T* data);

    virtual void addAfterCurrent(T* data) {
        insAfterCurrent(data);
        goDn();
    }

        virtual void removeAll();


    virtual void deleteStart() {
        T* temp = removeStart();
        if (temp)
            delete temp;
    }

    virtual void deleteCurrent() {
        T* temp = removeCurrent();
        if (temp)
            delete temp;
    }

    virtual void deleteEnd() {
        T* temp = removeEnd();
        if (temp)
            delete temp;
    }

    virtual void deleteAll() {
        while(linkCount)
            deleteStart();
        ListBase::init();
    }

        virtual void set(ListBase<T>& t) {
        deleteAll();
        append(t);
    }

    virtual void append(ListBase<T>& t) {
        t.savePtrs();
        t.goStart();
        for (int i = 0; i < t.size(); i++) {
            addEnd(t.getCurrent());
            t.goDn();
        }
        t.restPtrs();

    }

    virtual void operator = (ListBase<T>& t) {
        set(t);
    }

    virtual void operator +=(ListBase<T>& t) {
        append(t);
    }

    virtual void operator << (ListBase<T>& t) {
        set(t);
        t.removeAll();
    }

    virtual T* isInList(T* ptr) {
        T* temp = NULL;
        savePtrs();
        goStart();
        for (int i = 0; i < linkCount; i++) {
            T* currData = getCurrent();
            if (currData == ptr)
                temp = currData;
            goDn();
        }
        restPtrs();
        return temp;
    }

// for the RemoveByxxx functions, be sure to check the saved pointers after
// and make adjustments if they referenced the deleted item
// note: for moment, modifies list pointers,
    virtual T* removeByInstance(T* ptr) {
        T* temp = NULL;
        goStart();
        for (unsigned long i = 0; i < size(); i++) {
            temp = getCurrent();
            if (temp == ptr)
                return removeCurrent();
            goDn();
        }
        return NULL;
    }

    virtual T* removeByIndex(unsigned long index) {
        T* temp = NULL;

        goStart();
        for (unsigned long i = 0; i < index; i++)
            goDn();
        temp = removeCurrent();
        return temp;
    }

    virtual T* getByInstance(T* ptr) {
        T* temp = NULL;
        savePtrs();
        goStart();
        for (int i = 0; i < linkCount; i++) {
            T* currData = getCurrent();
            if (currData == ptr)
            {
                temp = currData;
                break;
            }
            goDn();
        }
        restPtrs();

        return temp;
    }

    virtual T* getByIndex(unsigned long i) { // uses 1 based index
        T* temp = NULL;
        savePtrs();
        goStart();
        if (i) {
            while (--i)
                goDn();
            temp = getCurrent();
        }
        restPtrs();
        return temp;
    }

};

//=========================================================================
// SingleList : creates a single linked list
//=========================================================================
template <class T>
class SingleList : public ListBase<T> {
protected:
    snode<T>* getPrevious(snode<T>* cur) {// finds the node before the current, null if not/
        snode<T>* temp = (snode<T>*)ListBase<T>::start;
        if (!temp)       // list is empty
            return NULL;
        if (!temp->next) // if only 1 node in list
            return NULL;
        if (temp == cur)	   // if current is the first node
            return NULL;
        while (temp && temp->next && temp->next != cur)
            temp = (snode<T>*)temp->next;
        return temp;
    }

public:
    SingleList() : ListBase<T>()	{ ListBase<T>::init(); }

    virtual T* goUp() { snode<T>* prev = getPrevious((snode<T>*)ListBase<T>::current); if (prev) ListBase<T>::current = prev;return (prev) ? ((snode<T>*)prev)->data : NULL; }

    virtual void addStart(T* data) {
        snode<T>* newLink = new snode<T>;
        newLink->data = data;		// copy data over to new link
        newLink->next = ListBase<T>::start;
        if (!ListBase<T>::linkCount++) {
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        ListBase<T>::start = newLink;
    }

    virtual void addEnd(T* data) {
        snode<T>* newLink = new snode<T>;
        newLink->data = data;
        newLink->next = NULL;
        if (ListBase<T>::linkCount++)
            ((snode<T>*)ListBase<T>::end)->next = newLink;
        else {
            ListBase<T>::start = newLink;
            ListBase<T>::current = newLink;
        }
        ListBase<T>::end = newLink;
    }

    virtual void insBeforeCurrent(T* data) {
        snode<T>* newLink = new snode<T>;
        newLink->data = data;
        if (!ListBase<T>::linkCount++) {
            newLink->next = NULL;
            ListBase<T>::start = newLink;
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        else {
            snode<T>* prev = getPrevious((snode<T>*)ListBase<T>::current);
            if (prev) // there exists a previous node
                prev->next = newLink;
            else
                ListBase<T>::start = newLink;
            newLink->next = ListBase<T>::current;
        }
    }

    virtual void insAfterCurrent(T* data) {
        snode<T>* newLink = new snode<T>;
        newLink->data = data;
        if (!ListBase<T>::linkCount++) {
            newLink->next = NULL;
            ListBase<T>::start = newLink;
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        else {
            newLink->next = ((snode<T>*)ListBase<T>::current)->next;
            if (!newLink->next)
                ListBase<T>::end = newLink;
            ((snode<T>*)ListBase<T>::current)->next = newLink;
        }
    }

    virtual T* removeStart() {
        T* ret = NULL;
        snode<T>* temp = NULL;
        if (ListBase<T>::start) {
            if (((snode<T>*)ListBase<T>::start)->next) {
                temp = (snode<T>*)((snode<T>*)ListBase<T>::start)->next;
                if (ListBase<T>::current == ListBase<T>::start)
                    ListBase<T>::current = temp;
            }
            else {
                temp = NULL;
                ListBase<T>::end = NULL;
                ListBase<T>::current = NULL;
            }
            ret = ((snode<T>*)ListBase<T>::start)->data;
            ((snode<T>*)ListBase<T>::start)->data = NULL;
            delete((snode<T>*)ListBase<T>::start);
            ListBase<T>::start = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }

    virtual T* removeCurrent() {
        T* ret = NULL;
        snode<T>* prev = getPrevious((snode<T>*)ListBase<T>::current);
        if (ListBase<T>::current) {
            if (!((snode<T>*)ListBase<T>::current)->next)
                ListBase<T>::end = prev;

            if (prev)
                prev->next = ((snode<T>*)ListBase<T>::current)->next;
            else
                ListBase<T>::start = ((snode<T>*)ListBase<T>::current)->next;

            snode<T>* temp;
            if (prev)        					// default assing new current to previous node
                temp = prev;
            else if (((snode<T>*)ListBase<T>::current)->next)
                temp =(snode<T>*)((snode<T>*)ListBase<T>::current)->next;
            else {
                temp = NULL;
                ListBase<T>::start = NULL;
                ListBase<T>::end = NULL;

            }
            if (ListBase<T>::start == ListBase<T>::current)
                ListBase<T>::start = (((snode<T>*)ListBase<T>::start)->next)?((snode<T>*)ListBase<T>::start)->next:NULL;
            if (ListBase<T>::end == ListBase<T>::current)
                ListBase<T>::end = (prev)?prev:NULL;

            ret = ((snode<T>*)ListBase<T>::current)->data;
            ((snode<T>*)ListBase<T>::current)->data = NULL;
            delete((snode<T>*)ListBase<T>::current);
            ListBase<T>::current = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }

    virtual T* removeEnd() {
        T* ret = NULL;
        snode<T>* temp = NULL;
        snode<T>* prev = getPrevious((snode<T>*)ListBase<T>::end);
        if (ListBase<T>::end) {
            if (prev) {
                temp = prev;
                if (ListBase<T>::current == ListBase<T>::end)
                    ListBase<T>::current = temp;
            }
            else {
                temp = NULL;
                ListBase<T>::start = NULL;
                ListBase<T>::end = NULL;
            }
            ret = ((snode<T>*)ListBase<T>::end)->data;
            ((snode<T>*)ListBase<T>::end)->data = NULL;
            delete((snode<T>*)ListBase<T>::end);
            ListBase<T>::end = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }

};

//===========================================================================
// DoubleList : creates a double linked list
//===========================================================================
template <class T>
class DoubleList : public ListBase<T>
{
public:
    DoubleList() : ListBase<T>() { ListBase<T>::init(); }

    virtual T* goUp() { if (ListBase<T>::current) ListBase<T>::current = ((dnode<T>*)ListBase<T>::current)->prev;  return (ListBase<T>::current) ? ((dnode<T>*)ListBase<T>::current)->data : NULL; }

    virtual void addStart(T* data) {
        dnode<T>* newLink = new dnode<T>;
        newLink->data = data; // copy data over to new link
        newLink->next = ListBase<T>::start;
        newLink->prev = NULL;
        if (ListBase<T>::linkCount++)
            ( (dnode<T>*)ListBase<T>::start )->prev = newLink;
        else {
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        ListBase<T>::start = newLink;
    }

    virtual void addEnd(T* data) {
        dnode<T>* newLink = new dnode<T>;
        newLink->data = data;
        newLink->next = NULL;
        newLink->prev = ListBase<T>::end;
        if (ListBase<T>::linkCount++)
            ((dnode<T>*)ListBase<T>::end)->next = newLink;
        else {
            ListBase<T>::start = newLink;
            ListBase<T>::current = newLink;
        }
        ListBase<T>::end = newLink;
    }

    virtual void insBeforeCurrent(T* data) {
        dnode<T>* newLink = new dnode<T>;
        newLink->data = data;
        if (!ListBase<T>::linkCount++) {
            newLink->prev = NULL;
            newLink->next = NULL;
            ListBase<T>::start = newLink;
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        else {
            newLink->prev = ((dnode<T>*)ListBase<T>::current)->prev;
            if (newLink->prev)
                ((dnode<T>*)newLink->prev)->next = newLink;
            else
                ListBase<T>::start = newLink;
            newLink->next = ListBase<T>::current;
            ((dnode<T>*)ListBase<T>::current)->prev = newLink;
        }
    }

    virtual void insAfterCurrent(T* data) {
        dnode<T>* newLink = new dnode<T>;
        newLink->data = data;
        if (!ListBase<T>::linkCount++) {
            newLink->prev = NULL;
            newLink->next = NULL;
            ListBase<T>::start = newLink;
            ListBase<T>::end = newLink;
            ListBase<T>::current = newLink;
        }
        else {
            newLink->next = ( (dnode<T>*)ListBase<T>::current )->next;
            if (newLink->next)
                ( (dnode<T>*)newLink->next )->prev = newLink;
            else
                ListBase<T>::end = newLink;
            newLink->prev = ListBase<T>::current;
            ( (dnode<T>*)ListBase<T>::current )->next = newLink;
        }
    }

    virtual T* removeStart() {
        T* ret = NULL;
        dnode<T>* temp = NULL;
        if (ListBase<T>::start) {
            if ( ( (dnode<T>*)ListBase<T>::start )->next) {
                temp = (dnode<T>*)((dnode<T>*)ListBase<T>::start)->next;
                ((dnode<T>*)((dnode<T>*)ListBase<T>::start)->next)->prev = NULL;
                if (ListBase<T>::current == ListBase<T>::start)
                    ListBase<T>::current = temp;
            }
            else {
                temp = NULL;
                ListBase<T>::end = NULL;
                ListBase<T>::current = NULL;
            }
            ret = ((dnode<T>*)ListBase<T>::start)->data;
            ((dnode<T>*)ListBase<T>::start)->data = NULL;
            delete((dnode<T>*)ListBase<T>::start);
            ListBase<T>::start = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }

    virtual T* removeCurrent() {
        T* ret = NULL;
        if (ListBase<T>::current) {
            if (((dnode<T>*)ListBase<T>::current)->next)
                ((dnode<T>*)((dnode<T>*)ListBase<T>::current)->next)->prev = ((dnode<T>*)ListBase<T>::current)->prev;
            else
                ListBase<T>::end = (dnode<T>*)((dnode<T>*)ListBase<T>::current)->prev;

            if (((dnode<T>*)ListBase<T>::current)->prev)
                ((dnode<T>*)((dnode<T>*)ListBase<T>::current)->prev)->next = ((dnode<T>*)ListBase<T>::current)->next;
            else
                ListBase<T>::start = (dnode<T>*)((dnode<T>*)ListBase<T>::current)->next;

            dnode<T>* temp;
            if (((dnode<T>*)ListBase<T>::current)->prev)
                temp = (dnode<T>*)((dnode<T>*)ListBase<T>::current)->prev;
            else if (((dnode<T>*)ListBase<T>::current)->next)
                temp = (dnode<T>*)((dnode<T>*)ListBase<T>::current)->next;
            else {
                temp = NULL;
                ListBase<T>::start = NULL;
                ListBase<T>::end = NULL;

            }
            if (ListBase<T>::start == ListBase<T>::current)
                ListBase<T>::start = (((dnode<T>*)ListBase<T>::start)->next)?((dnode<T>*)ListBase<T>::start)->next:NULL;
            if (ListBase<T>::end == ListBase<T>::current)
                ListBase<T>::end = (((dnode<T>*)ListBase<T>::end)->prev)?((dnode<T>*)ListBase<T>::end)->prev:NULL;

            ret = ((dnode<T>*)ListBase<T>::current)->data;
            ((dnode<T>*)ListBase<T>::current)->data = NULL;

            delete((dnode<T>*)ListBase<T>::current);
            ListBase<T>::current = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }

    virtual T* removeEnd() {
        T* ret = NULL;
        dnode<T>* temp = NULL;
        if (ListBase<T>::end) {
            if (((dnode<T>*)ListBase<T>::end)->prev) {
                temp = (dnode<T>*)((dnode<T>*)ListBase<T>::end)->prev;
                ((dnode<T>*)((dnode<T>*)ListBase<T>::end)->prev)->next = NULL;
                if (ListBase<T>::current == ListBase<T>::end)
                    ListBase<T>::current = temp;
            }
            else {
                temp = NULL;
                ListBase<T>::start = NULL;
                ListBase<T>::end = NULL;
            }
            ret = ((dnode<T>*)ListBase<T>::end)->data;
            ((dnode<T>*)ListBase<T>::end)->data = NULL;
            delete((dnode<T>*)ListBase<T>::end);
            ListBase<T>::end = temp;
            ListBase<T>::linkCount--;
        }
        return ret;
    }
};


// member function implementation

// ListBase
template <class T>
void ListBase<T>::addBeforeCurrent(T* data) {
        insBeforeCurrent(data);
        goUp();
}


template <class T>
void ListBase<T>::removeAll() {
        while (linkCount--) {
                snode<T>* temp = (snode<T>*)((snode<T>*)start)->next;
                ((snode<T>*)start)->data = NULL;
                delete (snode<T>*)start;
                start = temp;
        }
        ListBase::init();
}

//SingleList


//DoubleList

#endif 
