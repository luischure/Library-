/**
 * @file CardShop.cpp
 * @author Luis Chure Ortiz
 * @brief 
 * @version 0.1
 * @date 2023-04-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

/**
   * @brief sorts the list by comparing adjacent items, after the first pass one of the items will be in their correct order and continue the passes until all items are sorted. 
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
template<typename Comparator>
int CardShop::bubbleSort(Comparator comp, std::string key){
 int swapping = 0;
 int size = getLength();
 for (int i = 0; i < size -1; i++){
  for (int j = 0; j < size - i -1; j++){
    int a = (key == "atk")? getItem(j+1)->getAtk() : getItem(j+1)->getDef(); 
    int b = (key == "atk")? getItem(j)->getAtk() : getItem(j)->getDef(); 
    if(comp(a,b)){
      swap(j,j+1);
      swapping++;
    }
  }
 }
 return swapping;
} 


/**
   * @brief the insertion sort takes the first item of the unsorted region and places it into its correct position in the sorted region. This step is analogous to taking a card from the table and inserting it into its proper position in your hand.
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
template<typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key){
 int size = getLength();
 int swapping = 0; 
 for (int i = 1; i < size; i++){
  int j = i; 
  if(key == "atk"){
  while((j > 0)&& comp(getItem(j)->getAtk(), getItem(j-1)->getAtk())){
    swap(j, j-1);
    j--;
    swapping++;
    }
  }
  else if(key == "def"){
  while((j > 0) && comp(getItem(j)->getDef(), getItem(j-1)->getDef())){
    swap(j, j-1);
    j--;
    swapping++;
    }
  }
}
return swapping; 
}


/**
   * @brief The merge sort is a recursive sorting algorithm that always gives the same performance, regardless of the initial order of the array items. Suppose that you divide the array into halves, sort each half, and then merge the sorted halves into one sorted array
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
template<typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key)
{
 int lhs = 0; 
 int rhs = getLength()-1;
 int merges = merge_helperFunction(comp, lhs, rhs, key);
 return merges;
}

/**
   * @brief The merge sort is a recursive sorting algorithm that always gives the same performance, regardless of the initial order of the array items. Suppose that you divide the array into halves, sort each half, and then merge the sorted halves into one sorted array
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @param lhs the left hand side of the list
   * @param rhs the right hand side of the list
   * @return int the number of swaps
   */
template<typename Comparator>
int CardShop::merge_helperFunction(Comparator comp, int lhs, int rhs, std::string key){
  int counter = 0;
  int merge = 0;
  if (lhs >= rhs){//would not be in correct order
  return 0; //base case
 }

 int middle = lhs + (rhs - lhs)/2;
 merge = merge_helperFunction(comp ,lhs,middle,key) + merge_helperFunction(comp,middle+1,rhs,key);
 std::vector<YGOCard*> temp(getLength());//vector consisting of a size of the item count but empty; 
 int i = lhs;
 int j = middle +1;
 int empty = 0;
 while(i <= middle && j <= rhs){
  if (key == "atk") {
    if (comp(getPointerTo(i)->getItem()->getAtk(), getPointerTo(j)->getItem()->getAtk())) {
      temp[empty] = getPointerTo(i)->getItem();
      i++;
    }
    else {
    temp[empty] = getPointerTo(j)->getItem();
    j++;
  }
    }
  else if (key == "def") {
    if (comp(getPointerTo(i)->getItem()->getDef(), getPointerTo(j)->getItem()->getDef())) {
      temp[empty] = getPointerTo(i)->getItem();
      i++;
    }
    else {
    temp[empty] = getPointerTo(j)->getItem();
      j++;
  }
  }
  empty++;
  counter++;
}

 while(i <= middle){
  temp[empty] = getItem(i);
  i++;
  empty++;
 }
 while(j <= rhs){
  temp[empty] = getItem(j);
  j++;
  empty++;
  }

  for (int z = lhs; z <= rhs; z++){
    getPointerTo(z)->setItem(temp[z-lhs]);
  }
 return counter; 
}


/**
   * @brief The partition induces relationships among the array items that are the ingredients of a recursive solution. Arranging the array items around the pivot p generates 
   * two smaller sorting problems—sort the left section of the array (S1), and sort the right section of the array (S2). The relationships between the pivot and the array items 
   * imply that once you solve the left and right sorting problems, you will have solved the original sorting problem. 
  * @tparam Comparator 
   * @param comp user input if the order is in acending or decending order
   * @param low the lower part of the list compared to the pivot point
   * @param high the upper part of the list compared to the pivot point
   * @param key the sorting is done by acending or decending order of the attack or defense points. this key signals which to do. 
   * @param swapper the swap counter variable passed by reference
   * 
   * @return int returns the number of partitions of the array. 
*/
template<typename Comparator>
int CardShop::partition(Comparator comp, int low , int high , std::string key, int& swapper){
  YGOCard* pivot = getItem(high);
  int a = low-1;

  for (int j = low ; j < high ; j++){
    YGOCard* comp_card = getItem(j);
    if(key == "atk"){
      if(comp(comp_card->getAtk(), pivot->getAtk())){
        a++;
        swap(a,j);
        swapper++;
      }
    }
    else if(key == "def"){
      if(comp(comp_card->getDef(), pivot->getDef())){
        a++;
        swap(a,j);
        swapper++;
      }
    }
  }
  swap(a+1,high);
  swapper++;
  return a+1; 
}

/**
   * @brief this is a quick sort helper function that selects a pivot point and performs the recurisve calls. 
   * 
   * @tparam Comparator 
   * @param comp user input if the order is in acending or decending order
   * @param low the lower part of the list compared to the pivot point
   * @param high the upper part of the list compared to the pivot point
   * @param key the sorting is done by acending or decending order of the attack or defense points. this key signals which to do. 
   * @param swapper the swap counter variable passed by reference
   */
template<typename Comparator>
void CardShop::q_helperFunction(Comparator comp, int low, int high, std::string key, int& swapper){
  if(low < high){ 
    int pivot_point = partition(comp, low, high , key, swapper);
    q_helperFunction(comp , low, pivot_point - 1, key, swapper);
    q_helperFunction(comp, pivot_point +1, high, key, swapper);
  }
}

/**
   * @brief The quick sort rearranges the entries in an array during the partitioning process. Each partition places one entry—the pivot—in its correct sorted position. The entries in each of the two subarrays that are before and after the pivot will remain in their respective subarrays.
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
template<typename Comparator>
  int CardShop::quickSort(Comparator comp, std::string key){
    int swapper = 0; 
    q_helperFunction(comp, 0, getLength()-1, key, swapper);
    return swapper; 
  }



