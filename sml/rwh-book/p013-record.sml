val london : { id : int, name : string } = { id=101, name="London" }
val _ = print ("#id london: " ^ Int.toString (#id london) ^ "\n")
val _ = print ("#name london: " ^ #name london ^ "\n\n")

val alice : { id : int, name : string, city : { id : int, name : string } } =
    { id=101, name="Alice", city={ id=201, name="London" } }
val _ = print ("#id alice: " ^ Int.toString (#id alice) ^ "\n")
val _ = print ("#name alice: " ^ #name alice ^ "\n")
val _ = print ("#id (#city alice): " ^ Int.toString (#id (#city alice)) ^ "\n")
val _ = print ("#name (#city alice): " ^ #name (#city alice) ^ "\n\n")

(* The following decomposes as follows:

   val person_id = 101
   val person_name = "Alice"
   val { id=city_id, name=city_name } = { id=201, name="London" }

   Then the last decomposition above further decomposes recursively as follows:

   val city_id = 201
   val city_name = "London" *)

val {
    id=person_id,
    name=person_name,
    city={
        id=city_id,
        name=city_name
    }
} = alice
val _ = print ("person_id: " ^ Int.toString person_id ^ "\n")
val _ = print ("person_name: " ^ person_name ^ "\n")
val _ = print ("city_id: " ^ Int.toString city_id ^ "\n")
val _ = print ("city_name: " ^ city_name ^ "\n\n")

type hyperlink = {
    protocol : string,
    domain : string,
    page : string
}
val example : hyperlink = {
    protocol="http",
    domain="example.com",
    page="/"
}
val _ = print (#protocol example ^ "://" ^ #domain example ^ #page example ^ "\n\n")

val { protocol=example_protocol, domain=_, page=_ } = example
val _ = print ("example_protocol: " ^ example_protocol ^ "\n")

val { protocol=example_domain, ...} = example
val _ = print ("example_domain: " ^ example_domain ^ "\n\n")

val { protocol, ... } = example
val _ = print ("protocol: " ^ protocol ^ "\n\n")

val { protocol, domain, ... } = example
val _ = print ("protocol: " ^ protocol ^ "\n")
val _ = print ("domain: " ^ domain ^ "\n\n")

val { protocol, domain, page } = example
val _ = print ("protocol: " ^ protocol ^ "\n")
val _ = print ("domain: " ^ domain ^ "\n")
val _ = print ("page: " ^ page ^ "\n")
