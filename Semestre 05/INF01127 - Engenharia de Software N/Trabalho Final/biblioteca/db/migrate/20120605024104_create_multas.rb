class CreateMultas < ActiveRecord::Migration
  def self.up
    create_table :multas do |t|
      t.references :pessoa
      t.references :emprestimo
      t.integer :total
      t.boolean :emAberto

      t.timestamps
    end
  end

  def self.down
    drop_table :multas
  end
end
