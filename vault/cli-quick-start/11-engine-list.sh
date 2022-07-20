export VAULT_ADDR=http://127.0.0.1:8200/

vault secrets list
read; echo

vault secrets enable kv
vault secrets list
vault kv list kv
read; echo

vault kv put kv/corp/hr/alice city=london country=uk
vault kv get kv/corp/hr/alice
vault kv list kv
read; echo

vault kv delete kv
vault secrets list
vault kv list kv
read; echo

vault secrets disable kv
vault secrets list
