; Zhenhao Zhang zzh133@u.rochester.edu



; List Function 


; (.element-of X L): Returns true (non-nil) if the element X is an element of the list L (test elements with equalp), otherwise false (nil)
(defun .element-of (X L) ; .是为了区分是不是内置function 不带. 是自己定义的
    (if (null L)
        nil
      (if (equalp X (car L)) ; car 是取第一个元素
          t
        (.element-of X (cdr L))))) ; cdr 是除了第一个以后的所有元素



; (.reverse L): Returns a list that contains the same elements as the list L, but in the reverse (opposite) order
(defun .reverse (L) ; L 是传入的list  
  (defun .inner (lst acc) ; acc 现在是空的
    (if (null lst)
        acc
        (.inner (cdr lst) (cons(car lst) acc)))) ; cons(element, list) 构建一个列表 (cons '1 '(2 3)) -> 1 2 3 
        ; car list 被加在 acc 中
  (.inner L '()))



; (.sum L): Assuming that list L contains numbers, returns their sum
 (defun .sum (L)
  (if (null L)
      0
    (+ (car L) (.sum (cdr L)))))



; (.filter F L): Returns a list containing only those elements of L for which Boolean function F returns true (non-nil)
; numberp 判断是不是数字
; lessthan3 x < 3
; lessthany x < y lamdba (x) 用于命名的一个函数
(defun .filter (F L)
  (if (null L)
      '()
    (if (funcall F (car L))
        (cons (car L) (.filter F (cdr L)))
      (.filter F (cdr L)))))




; Set Function


; (cardinality S): Returns the cardinality of (number of elements in) set S
(defun .cardinality (S)
  (if (null S)
      0
  (+ 1 (.cardinality (cdr S)))))



; (.contains S X): Returns true (non-nil) if the set S contains the element X (test elements with equalp), otherwise false (nil)(defun )
; equalp A B 比较两个数的元素是不是一样的
(defun .contains (S X)
  (if (null S)
      nil
    (if (equalp X (car S))
        t
      (.contains (cdr S) X))))



; (.intersection S1 S2): Returns the set that is the intersection of sets S1 and S2 (that is: L1 ∩ L2 ); test elements with equalp   
(defun .intersection (S1 S2)
  (if (null S1)
    nil
    (if (.contains S2 (car S1))
        (cons (car S1) (.intersection (cdr S1) S2))
      (.intersection (cdr S1) S2))))



; (.subseteq S1 S1): Returns true (non-nil) if S1 is a subset of or equal to set S2 (that is, if S1 ⊆ S2), otherwise return false (nil); test elements with equalp
(defun .subseteq (S1 S2)
  (if (null S1)
      t
    (if (.contains S2 (car S1))
        (.subseteq (cdr S1) S2)
      nil)))



; Math Functions


; (.complex= C1 C2): Returns true (non-nil) if the complex numbers C1 and C2 are equal. 
; Two complex numbers ⟨r1,i1⟩ and ⟨r2,i2⟩ are equal iff r1 = r2 and i1 = i2. You may assume that complex numbers are 
; represented using lists containing two elements where the first element is the real component of the number and the 
; second element is the imaginary part of the number. Test numbers using =


(defun .complex= (C1 C2)
  (and (= (car C1) (car C2)) ; and 逻辑与 true and true -> true
       (= (car (cdr C1)) (car (cdr C2))))) ; cadr 取最大元素



; (.mod X Y): Returns the remainder when positive integer X is divided by positive in- teger Y
(defun .mod (X Y)
  (if (< X Y)
    X
    (.mod (- X Y) Y)))



; (.dot-product V1 2): Returns the dot product of vectors V1 and V2. The dot prod- uct of two vectors v1 = ⟨v1,1,v1,2,...,v1,n⟩ and v2 = ⟨v2,1,v2,2,...,v2,n⟩ is
(defun .dot-product (V1 V2)
  (if (null V1)
      0
    (+ (* (car V1) (car V2)) (.dot-product (cdr V1) (cdr V2)))))



; (.gcd X Y): Returns the greatest common divisor (GCD) of the two given positive integers
(defun .gcd (X Y)
  (if (= Y 0)
      X
    (.gcd Y (.mod X Y))))


  











