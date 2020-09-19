#include <iostream>
#include "cl.cpp"

using namespace std;
int main() {
    cout << "Create first set and fill it" << endl;
    MySet<char> st(30);
    st.add(17);
    st.add(28);
    st.add(13);
    st.add(28);
    st.add(28);
    st.add(3);
    st.add(12);
    for(int i = 0; i < 30; i++)
        if(st.find(i))
            cout << i << ", ";
    cout << endl;

    cout << "Take copy of set" << endl;
    MySet<char> st2(st);
    for(int i = 0; i < 30; i++)
        if(st.find(i))
            cout << i << ", ";
    cout << endl;

    cout << "Find 18 in set" << endl;
    cout << st.find(18) << endl;
    cout << "No, we cant find 18" << endl;

    cout << "Find 17 in set" << endl;
    cout << st.find(17) << endl;
    cout << "Yes, we can find 17" << endl;

    cout << "Lets go remove 17 and add 18" << endl;
    st.remove(17);
    st.add(18);
    cout << "Find 18 in set" << endl;
    cout << st.find(18) << endl;

    cout << "Find 17 in set" << endl;
    cout << st.find(17) << endl;

    cout << "Success!" << endl;
    cout << "Lets go union two sets" << endl;
    MySet<char> st3 = st | st2;
    for(int i = 0; i < 30; i++)
        if(st3.find(i))
            cout << i << ", ";
    cout << endl;
    cout << "Lets go intersection two sets" << endl;
    MySet<char> st4 = st & st2;
    for(int i = 0; i < 30; i++)
        if(st4.find(i))
            cout << i << ", ";
    cout << endl;
    cout << "Show negation of set" << endl;
    MySet<char> st5 = negative(st);
    for(int i = 0; i < 30; i++)
        if(st5.find(i))
            cout << i << ", ";
    cout << endl;
    cout << "Create error!" << endl;
    st.find(122);

}