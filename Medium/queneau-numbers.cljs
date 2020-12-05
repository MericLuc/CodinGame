; Original solution from user "jdsimon"

(ns Solution
  (:gen-class))

(defn step-queneau [xs]
  (let [[frst scnd] (split-at (quot (count xs) 2) xs)]
    (concat (mapcat vector (reverse scnd) frst)
            (when (> (count scnd) (count frst))
              [(first scnd)]))))

(defn queneau-n [n]
  (let [q0 (step-queneau (range 1 (inc n)))]
    (take n (iterate step-queneau q0))))

(defn queneau? [xs]
  (= (last xs) (range 1 (inc (count (first xs))))))

(defn -main [& args]
  (let [qs (queneau-n (read))]
    (if (not (queneau? qs))
      (println "IMPOSSIBLE")
      (->> (map (partial clojure.string/join ",") qs)
(mapv println)))))