export VAULT_ADDR=http://127.0.0.1:8200/
vault kv put secret/corp/hr/alice city=london country=uk interest=music interest=theatre

vault kv get secret/corp/hr/alice
read

vault kv get -mount secret corp/hr/alice
read

vault kv get -mount secret/ corp/hr/alice
read

vault kv get -mount secret corp/hr/alice/
read

# No value found at corp/data/hr/alice
vault kv get -mount secret/corp hr/alice

# No value found at hr/data/alice
vault kv get -mount secret/corp/hr alice
