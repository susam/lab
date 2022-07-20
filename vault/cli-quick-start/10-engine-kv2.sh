export VAULT_ADDR=http://127.0.0.1:8200/

vault secrets enable kv-v2
vault secrets enable kv
vault secrets list
read

vault kv put secret/corp/hr/alice city=london country=uk
vault kv put kv-v2/corp/hr/alice city=cambridge country=uk
vault kv put kv/corp/hr/alice city=oxford country=uk
read

vault kv get -mount secret corp/hr/alice
vault kv get -mount kv-v2 corp/hr/alice
vault kv get -mount kv corp/hr/alice
read

vault kv get -mount secret/corp hr/alice # No value found at corp/data/hr/alice
vault kv get -mount kv-v2/corp hr/alice # No value found at corp/data/hr/alice
vault kv get -mount kv/corp hr/alice
