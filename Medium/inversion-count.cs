using System;
using System.Linq;
using System.Collections.Generic;

class Node {
    public long m_val, m_sze;
    public Node m_lft, m_rht;

    public Node(long p_val) {
        m_val = p_val;
        m_sze = 1;
    }

    public long addNode(Node p_n) {
        ++m_sze;
        if (p_n.m_val < m_val) {
            if (null == m_lft) {
                m_lft = p_n;
                return m_sze - 1;
            }
            return m_lft.addNode(p_n) + 1 + (m_rht?.m_sze ?? 0);
        }
        if (null == m_rht) {
            m_rht = p_n;
            return 0;
        }
        return m_rht.addNode(p_n);
    }
}

class Solution {
    static void Main(string[] args) {
        long[] nums = Array.ConvertAll(Console.ReadLine().Split(' '), long.Parse);
        long res    = 0;
        Node root   = null;
        for (int i = 0; i < nums[3]; i++) {
            nums[2] = nums[1] * nums[2] % nums[0];
            Node node = new Node(nums[2]);
            if (root == null) root = node;
            else res += root.addNode(node);
        }

        Console.WriteLine(res);
    }
}