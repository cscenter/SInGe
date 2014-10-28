#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <cstddef> // size_t

#include "../node.hpp"

class NodeTest : public testing::Test {
 protected:
  virtual void SetUp() {
    edges_node1_.push_back(std::make_pair('a', 9));
    edges_node1_.push_back(std::make_pair('$', 100500));

    for (const auto& edge : edges_node1_) {
      node1_.AddEdge(edge.first, edge.second);
    }
  }

  void EdgeExistenceTester(Node& node, const std::vector<std::pair<char, size_t> >& edges) {
    for (const auto& edge : edges) {
      char c = edge.first;
      size_t to = edge.second;
      
      ASSERT_TRUE(node.HasEdgeThrough(c));
      ASSERT_EQ(node.NextNodeThrough(c), to);
    }  
  }

  void IsSortedTester(Node& node) {
    char prev_c = 0;
    bool first_c = true;
    for (const auto& edge : node) {
      char c = edge.first;
      size_t to = edge.second;

      if  (first_c) {
        first_c = false;
      } else {
        ASSERT_TRUE(prev_c < c);
      }

      prev_c = c;
    }
  }

  void SizeTester(Node& node, size_t size) {
    ASSERT_EQ(node.end() - node.begin(), size);
  }

  Node node0_;
  Node node1_;
  std::vector<std::pair<char, size_t> > edges_node1_;
};

TEST_F(NodeTest, EdgeExistence) {
  EdgeExistenceTester(node1_, edges_node1_);
}

TEST_F(NodeTest, IsSorted) {
  IsSortedTester(node1_);
}

TEST_F(NodeTest, Size) {
  SizeTester(node1_, edges_node1_.size());
  SizeTester(node0_, 0);
}

