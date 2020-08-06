class CreatePessoaTipos < ActiveRecord::Migration
  def self.up
    create_table :pessoa_tipos do |t|
      t.string :nome

      t.timestamps
    end
  end

  def self.down
    drop_table :pessoa_tipos
  end
end
