#include "DoublyLinkedList.hpp"
#include <string> 
#include <iostream>
#include "CardShop.cpp"

int main (){
    /**
    DoublyLinkedList<int> my_list; 
    my_list.insert(0,2);
    my_list.insert(1,6);
    my_list.insert(2,5);
    my_list.insert(3,3);

    my_list.display();
    
    my_list.swap(0,1);
    my_list.display();
    */

    CardShop card_shop("cards.csv");
    //card_shop.display(); 
    //std::cout << "swaps:" << card_shop.bubbleSort(std::less<int>{} , "atk") << std::endl; 
    //card_shop.display(); 
   // std::cout << "swaps: " << card_shop.insertionSort(std::less<int>{} , "atk") <<std::endl; 
   std::cout << "swaps: " << card_shop.mergeSort(std::less<int> {}, "atk")<<std::endl;
    card_shop.display(); 



}
