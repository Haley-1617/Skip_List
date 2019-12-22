//
//  main.cpp
//  Skip_List
//
//  Created by Haley Lai on 12/15/19.
//  Copyright © 2019 Haley Lai. All rights reserved.
//

#include <iostream>

using namespace std;

class Node {
public:
   int data;
   Node **level;
   Node(int data): data(data) {}
   Node(int data, int lv);
};

Node::Node(int data, int lv) {
   this->data = data;
   level = new Node*[lv]();
}

class Skip_List {
private:
   static const int MAX_H;
   static const float P;
   Node *head;

public:
   Skip_List();
   Skip_List(const Skip_List &rhs);
   ~Skip_List();
   void insert(int value, int lv);
//   void remove(const int &value);
   void display();
   int size(Node &node);
   Skip_List& operator=(const Skip_List &rhs);

};

const int Skip_List::MAX_H = 5; //5 levels from 0-4
const float Skip_List::P = 2.5;

//Default Constructor for Skip_List
Skip_List::Skip_List() {
   head = new Node(0, MAX_H);
}

//Deconstructor
Skip_List::~Skip_List() {
   delete head;
}

//insert a node into the list with value and level pass in.
void Skip_List::insert(int value, int lv) {
   Node *newNode = new Node(value, lv);
   Node *temp = head;
   Node *arr[lv];

   for (int i = lv - 1; i >= 0; i--) {
      while(temp->level[i] != NULL && temp->level[i]->data < value) {
         temp = temp->level[i];
      }
      arr[i] = temp;
   }

   if(arr[0] == NULL) {
      for (int i = lv - 1; i >= 0; i--) {
         arr[i] = head;
      }
   }

   for (int i = lv - 1; i >= 0; i--) {
      newNode->level[i] = arr[i]->level[i];
      arr[i]->level[i] = newNode;
   }
}

//display the list
void Skip_List::display() {
   for (int lv = MAX_H - 1; lv >= 0; lv--) {
      cout << "Level(" << lv << "): ";
      Node *temp = head->level[lv];
      while(temp) {
         if(temp->level[lv] == nullptr) {
            cout << temp->data;
         } else {
            cout << temp->data << " -> ";
         }
         temp = temp->level[lv];
      }
      cout << endl;
   }
}

int main(int argc, const char * argv[]) {
   Skip_List test;
   test.insert(1, 5);
   test.insert(2, 4);
   test.insert(3, 3);
   test.insert(4, 2);
   test.insert(5, 1);
   test.insert(6, 5);
   test.insert(7, 4);
   test.insert(8, 3);
   test.insert(9, 2);
   test.insert(10, 1);
   test.display();
   return 0;
}
