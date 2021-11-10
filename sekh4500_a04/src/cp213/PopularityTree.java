package cp213;

/**
 * Implements a Popularity Tree. Extends BST.
 *
 * @author Gurman Sekhon
 * @author David Brown
 * @version 2021-02-18
 */
public class PopularityTree<T extends Comparable<T>> extends BST<T> {

    /**
     * Auxiliary method for {@code valid}. May force node rotation if the retrieval
     * count of the located node value is incremented.
     *
     * @param node The node to examine for key.
     * @param key  The value to search for. Count is updated to count in matching
     *             node value if key is found.
     * @return the updated node.
     */
    private TreeNode<T> retrieveAux(TreeNode<T> node, final CountedData<T> key) {

    	if (node == null) {
			key.setCount(0);
		} else {
			final int result = node.getValue().compareTo(key);
			this.comparisons++;

			if (result > 0) {
				node.setLeft(this.retrieveAux(node.getLeft(), key));

				if (node.getLeft() != null && node.getValue().getCount() < node.getLeft().getValue().getCount()) {
					node = this.rotateRight(node);
				}
			} else if (result < 0) {
				node.setRight(this.retrieveAux(node.getRight(), key));

				if (node.getRight() != null && node.getValue().getCount() < node.getRight().getValue().getCount()) {
					node = this.rotateLeft(node);
				}
			} else {
				node.getValue().incrementCount();
				key.setCount(node.getValue().getCount());
			}
		}
		return node;

    }

    /**
     * Performs a left rotation around node.
     *
     * @param parent The subtree to rotate.
     * @return The new root of the subtree.
     */
    private TreeNode<T> rotateLeft(final TreeNode<T> parent) {

    			final TreeNode<T> temp = parent.getRight();
    			parent.setRight(temp.getLeft());
    			temp.setLeft(parent);
    			parent.updateHeight();
    			temp.updateHeight();
    			return temp;

    }

    /**
     * Performs a right rotation around {@code node}.
     *
     * @param parent The subtree to rotate.
     * @return The new root of the subtree.
     */
    private TreeNode<T> rotateRight(final TreeNode<T> parent) {

    	final TreeNode<T> temp = parent.getLeft();
		parent.setLeft(temp.getRight());
		temp.setRight(parent);
		parent.updateHeight();
		temp.updateHeight();
		return temp;

    }

    /**
     * Replaces BST {@code insertAux} - does not increment count on repeated
     * insertion. Counts are incremented only on retrieve.
     */
    @Override
    protected TreeNode<T> insertAux(TreeNode<T> node, final CountedData<T> data) {

    	if (node == null) {			
			node = new TreeNode<T>(data); 
			
			this.size++;
		} else {
			final int result = node.getValue().compareTo(data);

			if (result > 0) {
				node.setLeft(this.insertAux(node.getLeft(), data));
			} else if (result < 0) {
				node.setRight(this.insertAux(node.getRight(), data));
			}
		}
		node.updateHeight();
		return node;

    }

    /**
     * Auxiliary method for {@code valid}. Determines if a subtree based on node is
     * a valid subtree. An Popularity Tree must meet the BST validation conditions,
     * and additionally the counts of any node data must be greater than or equal to
     * the counts of its children.
     *
     * @param node The root of the subtree to test for validity.
     * @return true if the subtree base on node is valid, false otherwise.
     */
    @Override
    protected boolean isValidAux(final TreeNode<T> node) {

    	boolean valid = false;

		if (node == null) {
			valid = true;
		} else if (Math.max(this.nodeHeight(node.getLeft()), this.nodeHeight(node.getRight())) != node.getHeight()
				- 1) {
			valid = false;
		} else if (node.getLeft() != null && node.getLeft().getValue().compareTo(node.getValue()) >= 0
				|| node.getRight() != null && node.getRight().getValue().compareTo(node.getValue()) <= 0) {
			valid = false;
		} else {
			valid = this.isValidAux(node.getLeft()) && this.isValidAux(node.getRight());
		}
		return valid;

    }

    /**
     * Very similar to the BST retrieve, but increments the data count here instead
     * of in the insertion.
     *
     * @param key The key to search for.
     */
    @Override
    public CountedData<T> retrieve(CountedData<T> key) {

    	this.root = this.retrieveAux(this.root, key);
		if (key.getCount() == 0) {
			key = null;
		} else {
			key = new CountedData<T>(key);
		}
		return key;

    }

    /**
     * Determines whether two PopularityTrees are identical.
     *
     * @param target The PopularityTree to compare this PopularityTree against.
     * @return true if this PopularityTree and target contain nodes that match in
     *         position, value, count, and height, false otherwise.
     */
    public boolean equals(final PopularityTree<T> target) {
	return super.equals(target);
    }

}
