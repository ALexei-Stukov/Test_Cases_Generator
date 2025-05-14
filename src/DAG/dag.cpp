#include <memory>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

template <typename T>
class DAG {
public:
    class Node {
    public:
        T value;
        std::vector<Node*> parents;  // 父节点观察指针
        std::vector<Node*> children; // 子节点观察指针

        explicit Node(const T& val) : value(val) {}
    };

    // 修改后的先序遍历迭代器（支持路径记录）
    class PreorderIterator {
    public:
        struct StackItem {
            Node* node;
            std::vector<Node*> path;  // 从根节点到当前节点的路径历史
        };
        
        std::stack<StackItem> traversal_stack;

    public:
        explicit PreorderIterator(Node* root) {
            if (root != nullptr) {
                StackItem root_item;
                root_item.node = root;
                root_item.path.push_back(root);
                traversal_stack.push(root_item);
            }
        }

        PreorderIterator() = default;  // End迭代器

        const T& operator*() const { return traversal_stack.top().node->value; }
        T& operator*() { return traversal_stack.top().node->value; }

        PreorderIterator& operator++() {
            if (traversal_stack.empty()) return *this;

            // 弹出当前节点及其历史路径
            StackItem current_item = traversal_stack.top();
            traversal_stack.pop();

            Node* current = current_item.node;
            std::vector<Node*>& current_path = current_item.path;

            // 🌟 如果出现度为0，输出历史路径
            if (current->children.empty()) {
                std::cout << "Path to node " << current->value << " (out-degree 0): ";
                for (size_t i = 0; i < current_path.size(); ++i) {
                    std::cout << current_path[i]->value;
                    if (i < current_path.size() - 1) std::cout << " -> ";
                }
                std::cout << "\n";
            }

            // 子节点按逆序压栈（保证后续正序访问）
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                Node* child = *it;

                // 为子节点构建新路径
                StackItem child_item;
                child_item.node = child;
                child_item.path = current_path;  // 继承父路径
                child_item.path.push_back(child);  // 追加当前子节点

                traversal_stack.push(child_item);
            }

            return *this;
        }

        bool operator!=(const PreorderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreorderIterator& other) const {
            return traversal_stack.empty() && other.traversal_stack.empty();
        }
    };

private:
    std::vector<std::unique_ptr<Node>> nodes;

public:
    Node* add_node(const T& value) {
        nodes.push_back(std::make_unique<Node>(value));
        return nodes.back().get();
    }

    // 添加边（需自行确保无环）
    void add_edge(Node* parent, Node* child) {
        parent->children.push_back(child);
        child->parents.push_back(parent);
    }

    // 从单个根节点遍历
    PreorderIterator begin(Node* root) {
        return PreorderIterator(root);
    }

    PreorderIterator end() {
        return PreorderIterator();
    }

    // 获取所有根节点（入度为0）
    std::vector<Node*> get_roots() {
        std::vector<Node*> roots;
        for (auto& node : nodes) {
            if (node->parents.empty()) {
                roots.push_back(node.get());
            }
        }
        return roots;
    }
};

// int main() {
//     DAG<int> graph;

//     // 构造示例图: 
//     // 根1的分支：1 → 2 → 4（出度0）
//     // 根1的另一分支：1 → 3 → 4（出度0）
//     auto* node1 = graph.add_node(1);
//     auto* node2 = graph.add_node(2);
//     auto* node3 = graph.add_node(3);
//     auto* node4 = graph.add_node(4);

//     graph.add_edge(node1, node2);
//     graph.add_edge(node1, node3);
//     graph.add_edge(node2, node4);
//     graph.add_edge(node3, node4);

//     // 遍历
//     std::cout << "First traversal path:\n";
//     for (auto it = graph.begin(node1); it != graph.end(); ++it) {
//         // 普通遍历仍正常输出每个节点的值
//         std::cout << "Visiting node: " << *it << std::endl;
//     }

//     return 0;
// }