#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <cstddef> // size_t

#include "../suffix_automaton.hpp"

class SuffixAutomatonTest : public testing::Test {
 protected:
  virtual void SetUp() {}

  void NodeEqualsTest(Node correct_node, Node aut_node, std::string msg) {
    ASSERT_EQ(correct_node.link, aut_node.link) << msg;
    ASSERT_EQ(correct_node.len_actual, aut_node.len_actual) << msg;
    ASSERT_EQ(correct_node.len_within_document, aut_node.len_within_document) << msg;

    std::vector<std::pair<char, size_t> > correct_vec(correct_node.begin(), correct_node.end());
    std::vector<std::pair<char, size_t> > aut_vec(aut_node.begin(), aut_node.end());
    ASSERT_EQ(correct_vec, aut_vec) << msg;
  }
};

TEST_F(SuffixAutomatonTest, StructureTest) {
  SuffixAutomaton automaton;
  automaton.AddString("abacc", 5);

  ASSERT_EQ(automaton.AmountNodes(), 8);

  // node[0]
  ASSERT_EQ(automaton.GetNode(0), nullptr);
  
  // node[1]
  Node node1;
  node1.link = 0;
  node1.AddEdge('a', 2);
  node1.AddEdge('b', 3);
  node1.AddEdge('c', 7);
  node1.len_actual = node1.len_within_document = 0;
  ASSERT_NE(automaton.GetNode(1), nullptr);
  NodeEqualsTest(*automaton.GetNode(1), node1, " in automaton for \"abacc\" in node with id=" + std::to_string(1));

  // node[2]
  Node node2;
  node2.link = 1;
  node2.AddEdge('b', 3); 
  node2.AddEdge('c', 5);
  node2.len_actual = node2.len_within_document = 1;
  ASSERT_NE(automaton.GetNode(2), nullptr);
  NodeEqualsTest(*automaton.GetNode(2), node2, " in automaton for \"abacc\" in node with id=" + std::to_string(2));

  // node[3]
  Node node3;
  node3.link = 1;
  node3.AddEdge('a', 4);
  node3.len_actual = node3.len_within_document = 2;
  ASSERT_NE(automaton.GetNode(3), nullptr);
  NodeEqualsTest(*automaton.GetNode(3), node3, " in automaton for \"abacc\" in node with id=" + std::to_string(3));

  // node[4]
  Node node4;
  node4.link = 2;
  node4.AddEdge('c', 5);
  node4.len_actual = node4.len_within_document = 3;
  ASSERT_NE(automaton.GetNode(4), nullptr);
  NodeEqualsTest(*automaton.GetNode(4), node4, " in automaton for \"abacc\" in node with id=" + std::to_string(4));

  // node[5]
  Node node5;
  node5.link = 7;
  node5.AddEdge('c', 6);
  node5.len_actual = node5.len_within_document = 4;
  ASSERT_NE(automaton.GetNode(5), nullptr);
  NodeEqualsTest(*automaton.GetNode(5), node5, " in automaton for \"abacc\" in node with id=" + std::to_string(5));

  // node[6]
  Node node6;
  node6.link = 7;
  node6.len_actual = node6.len_within_document = 5;
  ASSERT_NE(automaton.GetNode(6), nullptr);
  NodeEqualsTest(*automaton.GetNode(6), node6, " in automaton for \"abacc\" in node with id=" + std::to_string(6));

  // node[7]
  Node node7;
  node7.link = 1;
  node7.len_actual = node7.len_within_document = 1;
  node7.AddEdge('c', 6);
  ASSERT_NE(automaton.GetNode(7), nullptr);
  NodeEqualsTest(*automaton.GetNode(7), node7, " in automaton for \"abacc\" in node with id=" + std::to_string(7));
}

TEST_F(SuffixAutomatonTest, EmptyStringTest) {
  SuffixAutomaton automaton;
  automaton.AddString("", 0);

  ASSERT_EQ(automaton.GetNode(0), nullptr);
  ASSERT_EQ(automaton.AmountNodes(), 2); // nullptr and root
}

TEST_F(SuffixAutomatonTest, DefaultConstructorTest) {
  SuffixAutomaton automaton;

  ASSERT_EQ(automaton.GetNode(0), nullptr);
  ASSERT_EQ(automaton.AmountNodes(), 2); // nullptr and root    
}

TEST_F(SuffixAutomatonTest, AddingViaStopSymbolTest) {
  SuffixAutomaton correct_automaton;
  correct_automaton.AddString("abacaba", 7);
  correct_automaton.AddStringViaStopSymbol("qwerty", 6);

  SuffixAutomaton automaton;
  automaton.AddString("abacaba", 7);
  automaton.AddStringViaStopSymbol("qw", 2);
  automaton.AddString("erty", 4);

  ASSERT_EQ(correct_automaton.AmountNodes(), automaton.AmountNodes()) << " comparing \"abacaba[stop]qwerty\" vs \"abacaba[stop]qw+erty";
  for (size_t id = 1; id < automaton.AmountNodes(); ++id) {
    NodeEqualsTest(*correct_automaton.GetNode(id), *automaton.GetNode(id), " comparing \"abacaba[stop]qwerty\" vs \"abacaba[stop]qw+erty, node id = " + std::to_string(id));
  }
}

