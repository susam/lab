(require "asdf")

(let ((*standard-output* (make-broadcast-stream)))
  (asdf:load-system "cxml"))

(defun node-text (node tag-name)
  (with-output-to-string (out)
    (let ((tag-nodes (dom:get-elements-by-tag-name node tag-name)))
      (when (plusp (dom:length tag-nodes))
        (let ((tag-node (dom:item tag-nodes 0)))
          (dom:do-node-list (tag-child-node (dom:child-nodes tag-node))
            (when (dom:text-node-p tag-child-node)
              (write-string (dom:data tag-child-node) out))))))))

(defun read-dom (doc)
  (format t "document-element: ~s~%" (dom:node-name (dom:document-element doc)))
  (dom:do-node-list (book (dom:get-elements-by-tag-name doc "book"))
    (format t "~%author: ~s~%" (node-text book "author"))
    (format t "title: ~s~%" (node-text book "title"))
    (format t "edition: ~s~%" (node-text book "edition"))
    (format t "year: ~s~%" (node-text book "year"))))

(read-dom (cxml:parse-file "books.xml" (cxml-dom:make-dom-builder)))

