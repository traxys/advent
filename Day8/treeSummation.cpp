#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
struct MetadataTree{
	std::vector< MetadataTree<T> > children;
	std::vector<T> metadata;

	explicit MetadataTree(std::istream* is){
		uint64_t childCount;
		uint64_t metadataCount;
		(*is) >> childCount >> metadataCount;
		for(uint64_t i = 0; i < childCount; ++i){
			children.push_back( MetadataTree<T>(is) );
		}
		if(children.size() != childCount){
			std::cerr << "INVALID CHILD SIZE" << std::endl;
		}
		for(uint64_t i = 0; i < metadataCount ; ++i){
			T data;
			(*is) >> data;
			metadata.push_back(data);
		}
		if(metadata.size() != metadataCount){
			std::cerr << "INVALID METADATA SIZE" << std::endl;
		}
	}
};

int sumMetadata(const MetadataTree<int>& tree){
	int sum = 0;
	for(auto& md : tree.metadata){
		sum += md;
	}
	for(auto& child : tree.children){
		sum += sumMetadata(child);
	}
	return sum;
}

int treeValue(const MetadataTree<int>& tree){
	int value = 0;
	if(tree.children.empty()){
		for(auto& md : tree.metadata){
			value += md;
		}
	}
	else{
		size_t childCount = tree.children.size();
		for(auto& md : tree.metadata){
			if(md == 0)
				continue;
			size_t index = md - 1;
			if(index < childCount){
				value += treeValue(tree.children[index]);
			}
		}
	}
	return value;
}

int main(){
	std::ifstream f("inputs/day8");
	MetadataTree<int> tree(&f);
	std::cout << "Sum of metadata : "<< sumMetadata(tree)
		<< std::endl;
	std::cout << "Value of tree : " << treeValue(tree)
		<< std::endl;
}
