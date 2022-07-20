export VAULT_ADDR=http://127.0.0.1:8200/

vault kv get foo/bob
read

vault kv get -mount foo bob
read

vault kv put foo/bob city=london
read

vault kv put -mount foo bob city=london
read
