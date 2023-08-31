/**
 * @file CardShop.hpp
 * @author Luis Chure Ortiz
 * @brief 
 * @version 0.1
 * @date 2023-04-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

  /**
   * @brief sorts the list by comparing adjacent items, after the first pass one of the items will be in their correct order and continue the passes until all items are sorted. 
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
  template<typename Comparator>
  int bubbleSort(Comparator comp, std::string key);

  /**
   * @brief the insertion sort takes the first item of the unsorted region and places it into its correct position in the sorted region. This step is analogous to taking a card from the table and inserting it into its proper position in your hand.
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
  template<typename Comparator>
  int insertionSort(Comparator comp, std::string key);

  /**
   * @brief The quick sort rearranges the entries in an array during the partitioning process. Each partition places one entry—the pivot—in its correct sorted position. The entries in each of the two subarrays that are before and after the pivot will remain in their respective subarrays.
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
  template<typename Comparator>
  int quickSort(Comparator comp, std::string key);

  /**
   * @brief The merge sort is a recursive sorting algorithm that always gives the same performance, regardless of the initial order of the array items. Suppose that you divide the array into halves, sort each half, and then merge the sorted halves into one sorted array
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
  template<typename Comparator>
  int mergeSort(Comparator comp, std::string key);

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
  int partition(Comparator comp, int low , int high , std::string key, int& swapper);

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
  void q_helperFunction(Comparator comp, int low, int high, std::string key, int& swapper);

  /**
   * @brief The merge sort is a recursive sorting algorithm that always gives the same performance, regardless of the initial order of the array items. Suppose that you divide the array into halves, sort each half, and then merge the sorted halves into one sorted array
   * 
   * @tparam Comparator 
   * @param comp this will be a user input of whether the sorting is in ascending order or decending order
   * @param key the sorting is done based on attack or defense points therefore the key will dictate which catagory the program will sort. 
   * @return int the number of swaps
   */
  template<typename Comparator>
  int merge_helperFunction(Comparator comp, int lhs, int rhs, std::string key);

};

#endif