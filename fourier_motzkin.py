import numpy as np

#check if pos, neg or zero
def check_value(val):
    if val > 0:
        return -2
    elif val<0:
        return -1
    else:
        return 0
#to avoid division by zero
def row_divide(row):
	if row[0]!=0:
		return row/np.abs(row[0])
	else:
		return row

#main function
def fm(A, c, n):
    print("Before:", A)
    #put elimination variable in first col
    A = rearrange_matrix(A, 1)
    print("After:", A)

    # add c to A matrix, right side
    T = np.hstack([A, c])
    print("stacked:", T)
    #sort columns, [neg, pos, zero]
    T = np.array(sorted(T, key=lambda x : check_value(x[0])))
    print("After sort:", T)
    #set constants
    s, r = T.shape

    n_pos = (T[:, 0]>0).nonzero()[0].size
    n_neg = n_pos + (T[:, 0]<0).nonzero()[0].size
    print("pos:", n_pos, "neg:",  n_neg)

    T = np.array(map(row_divide, T))
    print("after division:", T)

    s = s - n_neg + n_pos*(n_neg - n_pos)
    r = r - 1
    A = np.zeros((s, r))

    for i in xrange(n_pos):
        A[i*(n_neg - n_pos):(i+1)*(n_neg - n_pos), :] = T[i,1:]*np.ones([n_neg-n_pos, r])+T[n_pos:n_neg,1:]
    print(A)
    A[n_pos*(n_neg - n_pos):, :] = T[n_neg:, 1:]
    print(A)
    A = np.array(sorted(A, key=lambda x: check_value(x[0])))
    print("final", A)

def rearrange_matrix(A, n):
    r, s = A.shape
    I = np.identity(s)
    I[:, n-1] = np.zeros(s)
    I[0, n-1] = 1;
    I[:, 0] = np.zeros(s)
    I[n-1, 0] = 1
    return np.dot(A, I)

if __name__ == '__main__':
    A = np.array([[2.0, -11.0], [-3.0, 2.0], [1.0, 2.0], [-2.0, 1.0],[-4.0, 3.0], [0.0, 1.0], [0.0, 2.0]])

    b = np.array([[1.0],[1.0],[1.0],[1.0], [1.0], [1.0], [1.0]])

    print(fm(A, b, 2))
