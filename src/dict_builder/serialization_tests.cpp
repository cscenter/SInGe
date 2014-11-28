#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <cstddef> // size_t
#include <sstream>

#include "suffix_automaton.hpp"

class SerializationTest : public testing::Test {
protected:
  virtual void SetUp() {
  }

  void NodeEqualsTest(
      const Node& first_node,
      const Node& second_node,
      const std::string& msg) {
    EXPECT_EQ(first_node.link, second_node.link) << msg;
    EXPECT_EQ(first_node.len_actual, second_node.len_actual) << msg;
    EXPECT_EQ(first_node.len_within_document, second_node.len_within_document) << msg;
    EXPECT_EQ(first_node.docs_occurs_in, second_node.docs_occurs_in) << msg;
    EXPECT_EQ(first_node.score_occurs_only, second_node.score_occurs_only) << msg;
    EXPECT_EQ(first_node.last_hash, second_node.last_hash) << msg;
    EXPECT_EQ(first_node.edges_, second_node.edges_) << msg;
    EXPECT_EQ(first_node.rev_edges_, second_node.rev_edges_) << msg;
    EXPECT_EQ(first_node.rev_links_, second_node.rev_links_) << msg;
  }

  void AutomatonEqualsTest(
      const SuffixAutomaton& first_automaton,
      const SuffixAutomaton& second_automaton,
      const std::string& msg) {
    ASSERT_EQ(first_automaton.nodes_pool_.size(), second_automaton.nodes_pool_.size()) << msg;
    for (size_t i_node = 0; i_node < first_automaton.nodes_pool_.size(); ++i_node) {
      NodeEqualsTest(first_automaton.nodes_pool_[i_node], second_automaton.nodes_pool_[i_node], msg);
    }
    EXPECT_EQ(first_automaton.free_nodes_, second_automaton.free_nodes_) << msg;
    EXPECT_EQ(first_automaton.is_free_node_, second_automaton.is_free_node_) << msg;
    EXPECT_EQ(first_automaton.last_node_, second_automaton.last_node_) << msg;
    EXPECT_EQ(first_automaton.len_up_to_stop_symbol_, second_automaton.len_up_to_stop_symbol_) << msg;
    EXPECT_EQ(first_automaton.current_coef, second_automaton.current_coef) << msg;
    EXPECT_EQ(first_automaton.amount_alive_nodes_, second_automaton.amount_alive_nodes_) << msg;
    EXPECT_EQ(first_automaton.nodes_to_delete_, second_automaton.nodes_to_delete_) << msg;
    EXPECT_EQ(first_automaton.kMaxSize, second_automaton.kMaxSize) << msg;
    EXPECT_EQ(first_automaton.kCoef, second_automaton.kCoef) << msg;
    EXPECT_EQ(first_automaton.kStopSymbol, second_automaton.kStopSymbol) << msg;
  }

  SuffixAutomaton SerializeAndDeserialize(const SuffixAutomaton& automaton) {
    auto proto_automaton_ptr = automaton.GetProtoAutomaton();
    std::ostringstream output_stream;
    EXPECT_TRUE(proto_automaton_ptr->IsInitialized());
    proto_automaton_ptr->SerializeToOstream(&output_stream);
    std::istringstream input_stream(output_stream.str());
    ProtoAutomaton output_proto_automaton;
    output_proto_automaton.ParseFromIstream(&input_stream);
    return SuffixAutomaton(output_proto_automaton);
  }

  Node SerializeAndDeserialize(const Node& node) {
    auto proto_node_ptr = node.GetProtoNode();
    ProtoNode output_proto_node;
    output_proto_node.ParseFromString(proto_node_ptr->SerializeAsString());
    return Node(output_proto_node);
  }

  void AutomatonSerializationTest(const SuffixAutomaton& automaton) {
    AutomatonEqualsTest(automaton, SuffixAutomaton(*(automaton.GetProtoAutomaton())), "automaton construct, deconstruct test");
    AutomatonEqualsTest(automaton, SerializeAndDeserialize(automaton), "automaton Serialize and Deserialize test");
  }

  void NodeSerializationTest(const Node& node) {
    NodeEqualsTest(node, Node(*(node.GetProtoNode())), "node construct, deconstruct test");
    NodeEqualsTest(node, SerializeAndDeserialize(node), "node Serialize and Deserialize test");
  }

};

TEST(ProtobufVerify, Verify) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  EXPECT_NO_FATAL_FAILURE(GOOGLE_PROTOBUF_VERIFY_VERSION);
}

TEST_F(SerializationTest, NodeDefaultContructTest) {
  Node node1;
  NodeSerializationTest(node1);
}

TEST_F(SerializationTest, NodeManualContructTest) {
  Node node1;
  node1.link = 0;
  node1.AddEdge('a', 2);
  node1.AddEdge('b', 3);
  node1.AddEdge('c', 7);
  node1.AddRevEdge('x', 9);
  node1.AddRevLink(11);
  node1.len_actual = node1.len_within_document = 0;
  NodeSerializationTest(node1);

}

TEST_F(SerializationTest, EmptyStringTest) {
  SuffixAutomaton automaton;
  automaton.AddString("", 0);
  AutomatonSerializationTest(automaton);
}

TEST_F(SerializationTest, DefaultConstructorTest) {
  SuffixAutomaton automaton;
  AutomatonSerializationTest(automaton);
}

TEST_F(SerializationTest, AutomatonTest) {
  const char* str1 = "aaaabacaaabaca";
  const char* str2 = "xxxyyywwwwwwwwxxyyyw";
  const char* str3 = "l;kjasdalskdjfl  qojlsakj oit\n \n asl;fjlasjdfl;l;lkl;k354566325734 1```431@\n#$%^&*()";
  SuffixAutomaton automaton;
  automaton.AddString(str1, strlen(str1));
  automaton.AddString(str2, strlen(str2));
  automaton.AddString(str3, strlen(str3));
  AutomatonSerializationTest(automaton);
}

TEST_F(SerializationTest, AddingViaStopSymbolTest) {
  SuffixAutomaton automaton;
  automaton.AddString("abacaba", 7);
  automaton.AddStringViaStopSymbol("qw", 2);
  automaton.AddString("erty", 4);
  AutomatonSerializationTest(automaton);
}

