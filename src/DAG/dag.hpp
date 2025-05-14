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

            // 如果出现度为0，输出历史路径
            if (current->children.empty()) {
                // std::cout << "Path to end node (out-degree 0): ";
                
                //因为嵌套的关系，这里不能直接输出value。要么就重载一下运算符，不然就得这样双重嵌套。
                //不需要输出虚拟根节点，所以index从1开始。
                for (size_t i = 1; i < current_path.size(); ++i) {
                    // cout<<"(current_path[i]->value).type is"<<(current_path[i]->value).type<<std::endl;
                    if((current_path[i]->value).type == 0)
                    {
                        std::cout << (current_path[i]->value).int_value;
                        // std::cout << "branch A "<<(current_path[i]->value).int_value;
                    }
                    else
                    {
                        std::cout << (current_path[i]->value).lf_value;
                    }
                    // if (i < current_path.size() - 1) std::cout << " -> ";
                    if (i < current_path.size() - 1) std::cout << " ";
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
    //返回所有出度为0（子节点列表为空）的节点
    std::vector<Node*> get_all_outdegree_zero_nodes() {
        std::vector<Node*> zero_outdegree_nodes;
        for (const auto& node : nodes) {
            if (node->children.empty()) {
                zero_outdegree_nodes.push_back(node.get());
            }
        }
        return zero_outdegree_nodes;
    }

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