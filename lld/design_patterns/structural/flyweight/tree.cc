/*
Implement these classes:
1. TreeType
This is the Flyweight.
It should contain:
species
color
texture
and have a method:
Draw(int x, int y)
2. TreeFactory
This is the Flyweight Factory.
It should provide:
GetTreeType(...)
Requirements:
If the requested tree type doesn't exist, create it.
If it already exists, return the existing Flyweight.
Store the Flyweights internally.
The same tree type must return the same object.
3. Tree
This represents an individual tree.
It should contain:
x
y
TreeType
Important:
Tree should not store:
species
color
texture
because those belong to the Flyweight.
4. Forest
Create a class that can contain many trees.
It should have something like:
PlantTree(...)
which:
Gets the appropriate TreeType from the factory.
Creates an individual Tree.
Stores it.
And:
Draw()
which draws every tree.
Constraints
Use:
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
Use smart pointers.
Do not implement main() — I will provide it.
Your code should be compatible with the following main():
int main() {
    Forest forest;

    forest.PlantTree(10, 20, "Oak", "Green", "oak.png");
    forest.PlantTree(50, 80, "Oak", "Green", "oak.png");
    forest.PlantTree(100, 120, "Pine", "DarkGreen", "pine.png");
    forest.PlantTree(200, 300, "Oak", "Green", "oak.png");
    forest.PlantTree(500, 600, "Pine", "DarkGreen", "pine.png");

    forest.Draw();

    return 0;
}
Expected conceptual result
You should have:
TreeType objects:

Oak  ────────────────┐
                     │
                     ├── Tree at (10,20)
                     ├── Tree at (50,80)
                     └── Tree at (200,300)

Pine ────────────────┐
                     ├── Tree at (100,120)
                     └── Tree at (500,600)
So although there are 5 trees, there should only be 2 Flyweight objects:
Oak
Pine
One important C++ detail
Because the factory needs to return shared objects, think carefully about whether your return type should be:
TreeType*
or
std::shared_ptr<TreeType>
*/
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

class TreeType {
    std::string species_;
    std::string color_;
    std::string texture_;

public:
    TreeType(std::string species, std::string color, std::string texture)
        : species_(species),
          color_(color),
          texture_(texture) {}

    void Draw(int x, int y) const {
        std::cout << "Drawing " << species_
                  << " tree at (" << x << ", " << y << ")"
                  << " | Color: " << color_
                  << " | Texture: " << texture_
                  << "\n";
    }
};

class Tree {
    int x_;
    int y_;
    std::shared_ptr<TreeType> tree_type_;

public:
    Tree(int x, int y, std::shared_ptr<TreeType> tree_type)
        : x_(x),
          y_(y),
          tree_type_(std::move(tree_type)) {}

    void Draw() const {
        tree_type_->Draw(x_, y_);
    }
};

class TreeFactory {
    std::unordered_map<std::string, std::shared_ptr<TreeType>> tree_types_;

public:
    std::shared_ptr<TreeType> GetTreeType(
        const std::string& species,
        const std::string& color,
        const std::string& texture) {

        std::string key = species + "#" + color + "#" + texture;

        auto it = tree_types_.find(key);

        if (it != tree_types_.end()) {
            return it->second;
        }

        auto tree_type =
            std::make_shared<TreeType>(species, color, texture);

        tree_types_[key] = tree_type;

        return tree_type;
    }
};

class Forest {
    TreeFactory tree_factory_;
    std::vector<Tree> trees_;

public:
    void PlantTree(
        int x,
        int y,
        const std::string& species,
        const std::string& color,
        const std::string& texture) {

        std::shared_ptr<TreeType> tree_type =
            tree_factory_.GetTreeType(species, color, texture);

        trees_.emplace_back(x, y, tree_type);
    }

    void Draw() const {
        for (const auto& tree : trees_) {
            tree.Draw();
        }
    }
};

int main() {
    Forest forest;

    forest.PlantTree(10, 20, "Oak", "Green", "oak.png");
    forest.PlantTree(50, 80, "Oak", "Green", "oak.png");
    forest.PlantTree(100, 120, "Pine", "DarkGreen", "pine.png");
    forest.PlantTree(200, 300, "Oak", "Green", "oak.png");
    forest.PlantTree(500, 600, "Pine", "DarkGreen", "pine.png");

    forest.Draw();

    return 0;
}