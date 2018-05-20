(require '[clojure.string :as str])
(require '[clojure.core.reducers :as r])

;; (println "Hello World")
;; (println (read-line))
(defn parse-int [n] (Integer/parseInt n))
;; (def t (parse-int (read-line)))
(defn test-case [] (read-line)
                   (let [ts (map parse-int (str/split (read-line) #" "))
                         t (count ts)
                         ts-sum (r/fold + ts)
                         ; Unordered
                         ts-partial-sums (->> ts
                                              (r/reduce (fn [xs x] (conj xs (+ (peek xs) x))) (list 0))
                                              (into #{}))
                         divides (fn [a b] (= (rem b a) 0))
                         ; The sequence can be partitioned in k parts of equal sum
                         ; True if and only if k | sum and every multiple of sum / k
                         ; less than or equal to sum and greater than or equal to 0 are
                         ; in ts-partial-sums
                         works? (fn [k] (and (divides k ts-sum) 
                                             (every? ts-partial-sums (map (fn [x] (* x (quot ts-sum k))) (range 0 k)))))

                         result (map works? (range 1 (+ 1 t)))]
                         (println (str/join "" (map (fn [tr?] (if tr? 1 0)) result))))
)

(def t (parse-int (read-line)))
(dotimes [_ t] (test-case))
