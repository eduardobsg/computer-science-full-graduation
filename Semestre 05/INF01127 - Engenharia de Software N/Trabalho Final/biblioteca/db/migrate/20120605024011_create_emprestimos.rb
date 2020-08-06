class CreateEmprestimos < ActiveRecord::Migration
  def self.up
    create_table :emprestimos do |t|
      t.references :pessoa
      t.references :item
      t.date :dataDevolucao

      t.timestamps
    end
  end

  def self.down
    drop_table :emprestimos
  end
end
